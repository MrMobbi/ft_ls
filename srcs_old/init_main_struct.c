
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

static void ft_rearrange_order(t_ls *ls)
{
	t_path	*node = ls->path;
	t_path	*file_head = NULL;
	t_path	*file_node = NULL;
	t_path	*folder_head = NULL;
	t_path	*folder_node = NULL;
	while (node != NULL)
	{
		if (node->folder == true)
		{
			ft_option_file_sort_alpha(&node->file);
			if (folder_head == NULL)
			{
				folder_node = node;
				folder_head = folder_node;
			}
			else
			{
				folder_node->next = node;
				folder_node = folder_node->next;
			}
		}
		else
		{
			if (file_head == NULL)
			{
				file_node = node;
				file_head = file_node;
			}
			else
			{
				file_node->next = node;
				file_node = file_node->next;
			}
		}
		node = node->next;
	}
	if (file_node)
		file_node->next = NULL;
	if (folder_node)
		folder_node->next = NULL;
	ft_option_path_sort_alpha(&file_head);
	ft_option_path_sort_alpha(&folder_head);
	if (file_node != NULL)
	{
		file_node = file_head;
		while (file_node->next != NULL)
			file_node = file_node->next;
		if (file_node != NULL)
			file_node->next = folder_head;
	}

	ls->path = (file_head != NULL) ? file_head : folder_head;
}

static void	ft_apply_option(t_ls *ls)
{
	if (ft_option_checker(ls->option, E_OPTION_CR))
	{
		ft_apply_recursive(ls->path);
		ls->recur = true;
	}
	if (ft_option_checker(ls->option, E_OPTION_T))
		ft_apply_time(ls);
	if (ft_option_checker(ls->option, E_OPTION_R))
		(void) ls;
}

void	ft_init_main_struct(t_ls *ls, int ac, char **av)
{
	ft_token_prompt(ls, ac, av);
	ft_token_check(ls);
	ft_token_option_get(ls);
	ft_path_get(ls);
	ft_apply_option(ls);
	ft_rearrange_order(ls);
	//db_print_ls(ls);
}
