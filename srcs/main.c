
#include "../incl/ft_ls.h"

int	ft_quit(t_ls *ls)
{
	ft_lst_path_free(ls->path);
	return (ls->return_status);
}

int main(int ac, char **av)
{
	t_ls	ls = {};
	ft_extract_path_and_option(ac, av, &ls);
	ft_print(&ls);
	return (ft_quit(&ls));
}
