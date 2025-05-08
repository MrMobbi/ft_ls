
#include "../incl/ft_ls.h"

static int ft_return_status(t_path *path)
{
	while (path)
	{
		if (path->error)
			return (1);
		path = path->next;
	}
	return (0);
}

static int	ft_quit(t_ls *ls)
{
	ls->return_status = ft_return_status(ls->path);
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
