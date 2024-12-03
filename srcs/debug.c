
#include "../incl/ft_ls.h"

static void	db_print_token(t_token *start)
{
	t_token	*node = start;
	while (node != NULL)
	{
		printf("# token name [%s] # \n", node->name);
		printf("option [%s]\n", node->option ? "true" : "false");
		printf("path [%s]\n", node->path ? "true" : "false");
		node = node->next;
	}
}

static void	db_print_file(t_file *start)
{
	t_file	*node = start;
	while (node != NULL)
	{
		printf("# file name [%s] #\n", node->name);
		switch(node->type)
		{
			case (E_FILE):
				printf("it's a file\n");
				break;
			case (E_DIR):
				printf("it's a directory\n");
				break;
			case (E_EXEC):
				printf("it's an executable\n");
				break;
			default:
				printf("Unknown file\n");
		}
		node = node->next;
	}
}

static void	db_print_path(t_path *start)
{
	t_path	*node = start;
	while (node != NULL)
	{
		printf("# Path name [%s] #\n", node->name);
		printf("#### Printing FILE ####\n");
		if (node->file)
			db_print_file(node->file);
		else
			printf("it's a file and not a directory\n");
		node = node->next;
	}
}

void	db_print_ls(t_ls *ls)
{
	printf("---- DEBUG ----\n");
	printf("#### Printing TOKEN: ####\n");
	db_print_token(ls->token);
	printf("#### Printing PATH: ####\n");
	db_print_path(ls->path);
	printf("###\nls->option [%s]\n", ls->option);
}
