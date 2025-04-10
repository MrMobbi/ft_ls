
#include "../incl/ft_ls.h"

int main(int ac, char **av)
{
	t_ls	ls = {};
	ft_extract_path_and_option(ac, av, &ls);
	return (0);
}
