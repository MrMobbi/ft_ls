
#include "../incl/ft_ls.h"

void	ft_quit(t_ls *ls)
{
	ft_lst_token_free(ls->token);
	ft_lst_path_free(ls->path);
	if (ls->option == NULL)
		free(ls->option);
	exit(0);
}

int main(int ac, char **av)
{
	t_ls	ls = {};
	ft_init_main_struct(&ls, ac, av);
	ft_print(ls);
	ft_quit(&ls);
	return (0);
}
