
#include "../incl/ft_ls.h"

void	ft_quit(t_ls *ls)
{
	(void) ls;
	exit(0);
}

int main(int ac, char **av)
{
	t_ls	ls = {};
	ft_init_main_struct(&ls, ac, av);
	ft_print(&ls);
	ft_quit(&ls);
	return (0);
}
