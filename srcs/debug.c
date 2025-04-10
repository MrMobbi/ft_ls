
#include "../incl/ft_ls.h"

void	db_print_token(t_token *ptr)
{
	ft_printf("### TOKEN ###\n");
	while (ptr != NULL)
	{
		ft_printf("[%s]\n", ptr->name);
		if (ptr->option == true)
			ft_printf("Token is an option\n");
		else
			ft_printf("Token is a path\n");
		printf("\n");
		ptr = ptr->next;
	}
}
