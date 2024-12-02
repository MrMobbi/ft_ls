
#include "../incl/ft_ls.h"

static void	ft_token_prompt(t_ls *ls, int ac, char **av)
{
	for (int i = 1; i < ac; i ++)
	{
		if (i == 1)
			ls->token = ft_lst_token_new(av[i]);
		else
			ft_lst_token_add(ls->token,ft_lst_token_new(av[i]));
	}
}

static void	ft_token_check(t_ls *ls)
{
	// This function check if a path is given, 
	// if not the program will set a default path
	if (ls->token == NULL)
		ls->token = ft_lst_token_new(D_DEFAULT_PATH);
	else
	{
		bool path = false;
		t_token	*node = ls->token;
		while (node != NULL)
		{
			if (node->path)
				path = true;
			node = node->next;
		}
		if (!path)
			ft_lst_token_add(ls->token, ft_lst_token_new(D_DEFAULT_PATH));
	}
}

static void	ft_token_option_get(t_ls *ls)
{
	t_token	*node = ls->token;
	while (node != NULL)
	{
		if (node->option)
		{
			ft_option_check_dash(node->name);
			ls->option = ft_option_add(ls->option, node->name);
		}
		node = node->next;
	}
}

static void	ft_path_get(t_ls *ls)
{
	t_token	*node = ls->token;
	while (node != NULL)
	{
		if (node->path)
		{
			if (ls->path == NULL)
				ls->path = ft_lst_path_new(node->name);
			else
				ft_lst_path_add(ls->path, ft_lst_path_new(node->name));
		}
		node = node->next;
	}
}

void	ft_init_main_struct(t_ls *ls, int ac, char **av)
{
	ft_token_prompt(ls, ac, av);
	ft_token_check(ls);
	ft_token_option_get(ls);
	ft_path_get(ls);
	db_print_ls(ls);
}
