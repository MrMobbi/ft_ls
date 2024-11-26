
#include "../incl/ft_ls.h"

void	ft_exit(t_ls *ls)
{
	free(ls->path);
	closedir(ls->dir);
	free(ls);
}
