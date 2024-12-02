
#include "../incl/ft_ls.h"

void	db_print_token(t_token *start)
{
	t_token	*node = start;
	while (node != NULL)
	{
		printf("#### token name [%s] #### \n", node->name);
		printf("option [%s]\n", node->option ? "true" : "false");
		printf("path [%s]\n", node->path ? "true" : "false");
		node = node->next;
	}
}

void	db_print_path(t_path *start)
{
	t_path	*node = start;
	while (node != NULL)
	{
		printf("### Path name [%s] ###\n", node->name);
		printf("pointer to DIR [%p]\n", node->p_dir);
		printf("is a file [%s]\n", node->file ? "true" : "false");
		node = node->next;
	}
}
