
#include "../incl/ft_ls.h"

/* Tokenizing the prompt */
static	t_token	*ft_get_token(int ac, char **av)
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

/* It is possible that only the option has been
 * given in that case this function will add
 * the current folder as default path */
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

/* Will initiate the option for the main struc
 * and get all the paths for printing*/
static void	ft_get_path_and_option(t_ls *ls, t_token *token)
{
	ls->option = ft_option_get(token);
}

/* Manage how to endle the token */
void	ft_extract_path_and_option(int ac, char **av, t_ls *ls)
{
	t_token	*token;
	token = ft_get_token(ac, av);
	ft_token_check_path(token);
	ft_get_path_and_option(ls, token);

	db_print_token(token);
	ft_printf("ls->option [%s]", ls->option);
	ft_lst_token_free(token);
	(void) ls;
}
