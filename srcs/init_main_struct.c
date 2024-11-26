
#include "../incl/ft_ls.h"

static void	ft_file_get_name(t_ls *ls)
{
	struct dirent	*de;
	ls->dir = opendir(ls->path);
	if (ls->dir == NULL)
		exit(1); // todo exit function
	int i = 0;
	while ((de = readdir(ls->dir)) != NULL)
	{
		if (i == 0)
			ls->start = ft_list_new(de);
		else
			ft_list_add(ls->start, ft_list_new(de));
		i++;
	}
	db_list_print(ls->start);
}

t_ls *ft_init_main_struct(int ac, char **av)
{
	(void) av;
	t_ls *new = malloc(sizeof(t_ls));
	if (!new)
		exit(1); // todo exit function
	if (ac == 1)
	{
		new->path = malloc(sizeof(char) * 2);
		if (!new->path)
			exit(1); // todo exit function
		new->path[0] = '.';
		new->path[1] = '\0';
		printf("new->path = [%s]\n", new->path);
	}
	ft_file_get_name(new);
	return (new);
}
