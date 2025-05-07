
#include "../incl/ft_ls.h"

static t_token	*ft_get_token(int ac, char **av)
{
	t_token	*token = NULL;
	if (ac < 2)
		token = ft_lst_token_new(D_DEFAULT_PATH);
	for (int i = 1; i < ac; i++)
	{
		t_token	*nw = ft_lst_token_new(av[i]);
		if (token == NULL)
			token = nw;
		else
			ft_lst_token_add(token, nw);
	}
	return (token);	
}

static void	ft_token_check_path(t_token *ptr)
{
	bool	path = false;
	t_token *node = ptr;
	while (node != NULL)
	{
		if (node->option == false)
		{
			path = true;
			break ;
		}
		node = node->next;
	}
	if (!path)
		ft_lst_token_add(ptr, ft_lst_token_new(D_DEFAULT_PATH));
}

static void	ft_get_path_and_option(t_ls *ls, t_token *token)
{
	ls->option = ft_option_get(token);
	ls->path = ft_path_get(token, 
			ft_is_option(E_OPTION_A, ls->option),
			ft_is_option(E_OPTION_L, ls->option));
}

static void	ft_apply_option(t_ls *ls)
{
	t_option	option;
	option.hidden = ft_is_option(E_OPTION_A, ls->option);
	option.time = ft_is_option(E_OPTION_T, ls->option);
	option.reverse = ft_is_option(E_OPTION_R, ls->option);
	option.hidden = ft_is_option(E_OPTION_L, ls->option);
	ls->rec = ft_is_option(E_OPTION_CR, ls->option);
	ft_path_rearrange(ls, option);
}

static void	ft_is_multiple(t_ls *ls)
{
	t_path	*node = ls->path;
	int		count = 0;
	bool	file = false;
	while (node != NULL)
	{
		if (node->folder == false)
			file = true;
		if (file == true && count == 0)
			count++;
		if (node->folder == true)
			count++;
		node = node->next;
		if (count > 1)
		{
			ls->multiple = true;
			break;
		}
	}
}

void	ft_extract_path_and_option(int ac, char **av, t_ls *ls)
{
	t_token	*token;
	token = ft_get_token(ac, av);
	ft_token_check_path(token);
	ft_get_path_and_option(ls, token);
	ft_apply_option(ls);
	ft_is_multiple(ls);

	//db_print_token(token);
	//db_ls(ls);
	ft_lst_token_free(token);
}
