
#include "../incl/ft_ls.h"

void	db_print_token(t_token *start)
{
	t_token	*node = start;
	while (node != NULL)
	{
		printf("#\n");
		printf("token name [%s] # \n", node->name);
		printf("option [%s]\n", node->option ? "true" : "false");
		printf("path [%s]\n", node->path ? "true" : "false");
		node = node->next;
	}
}

void	db_print_file(t_file *start)
{
	t_file	*node = start;
	while (node != NULL)
	{
		printf("#\n");
		printf("file name [%s] #\n", node->name);
		printf("file path [%s]\n", node->path);
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
			case (E_CURRENT):
				printf("file is the current folder\n");
				break;
			case (E_PREVIOUS):
				printf("file is the previous folder\n");
				break;
			case (E_FILE_HIDE):
				printf("hiden file\n");
				break;
			case (E_DIR_HIDE):
				printf("hiden folder\n");
				break;
			case (E_EXEC_HIDE):
				printf("hiden executable\n");
				break;
			default:
				printf("Unknown file\n");
		}
		node = node->next;
}
}

void	db_print_path(t_path *start)
{
	t_path	*node = start;
	while (node != NULL)
	{
		printf(D_BLUE);
		printf("# PATH\n");
		printf(D_RESET);
		printf("Path name [%s] #\n", node->name);
		printf(D_RED);
		printf("#### Printing FILE ####\n");
		printf(D_RESET);
		if (node->file)
			db_print_file(node->file);
		else
			printf("it's a file and not a directory\n");
		node = node->next;
	}
}

void	db_print_ls(t_ls *ls)
{
	printf(D_BLUE);
	printf("---- DEBUG ----\n");
	printf(D_RESET);
	printf(D_CYAN);
	printf("#### Printing TOKEN: ####\n");
	printf(D_RESET);
	db_print_token(ls->token);
	printf(D_CYAN);
	printf("#### Printing PATHS and FILES: ####\n");
	printf(D_RESET);
	db_print_path(ls->path);
	printf(D_CYAN);
	printf("###\n");
	printf(D_RESET);
	printf("ls->option [%s]\n", ls->option);
}
