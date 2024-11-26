
#include "../incl/ft_ls.h"

int main(int ac, char **av)
{
	t_ls	*ls;
	ls = ft_init_main_struct(ac, av);
	if (!ls)
		return (1);
	ft_print(ls);
	ft_exit(ls);
	return (0);
}
