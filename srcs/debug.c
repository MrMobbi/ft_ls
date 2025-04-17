
#include "../incl/ft_ls.h"

void	db_print_token(t_token *ptr)
{
	ft_printf("### TOKEN ###\n");
	while (ptr != NULL)
	{
		ft_printf("[%s] ", ptr->name);
		if (ptr->option == true)
			ft_printf("Token is an option\n");
		else
			ft_printf("Token is a path\n");
		printf("\n");
		ptr = ptr->next;
	}
}

void	db_print_file(t_file *ptr)
{
	ft_printf("### FILE ###\n");
	while (ptr != NULL)
	{
		ft_printf("[%s] ", ptr->name);
		if (ptr->type == E_FOLDER)
			ft_printf("Is a folder\n");
		else if (ptr->type == E_HIDE)
			ft_printf("Is a hiden file\n");
		else if (ptr->type == E_OTHER)
			ft_printf("Is file or executable\n");
		else if (ptr->type == E_CURRENT)
			ft_printf("Is current\n");
		else if (ptr->type == E_PREVIOUS)
			ft_printf("Is previous\n");

		ptr = ptr->next;
	}
}

void	db_print_path(t_path *ptr)
{
	ft_printf("### PATH ###\n");
	while (ptr != NULL)
	{
		ft_printf("[%s] ", ptr->name);
		if (ptr->folder == true)
		{
			ft_printf("PATH is a folder:\n");
			db_print_file(ptr->file);
		}
		else
			ft_printf("PATH is a file \n");	
		ptr = ptr->next;
	}
}
