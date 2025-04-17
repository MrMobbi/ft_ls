
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
	ls->path = ft_path_get(token);
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
	ft_path_sort_alpha(&file_head);
	ft_path_sort_alpha(&folder_head);
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

/* Manage how to endle the token */
void	ft_extract_path_and_option(int ac, char **av, t_ls *ls)
{
	t_token	*token;
	token = ft_get_token(ac, av);
	ft_token_check_path(token);
	ft_get_path_and_option(ls, token);
	ft_rearrange_order(ls);

	ft_printf("ls->option [%s]\n", ls->option);
	db_print_token(token);
	db_print_path(ls->path);
	ft_lst_token_free(token);
}
