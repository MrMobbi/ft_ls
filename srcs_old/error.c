
#include "../incl/ft_ls.h"

void	ft_error(char *msg, int rt_error)
{
	perror(msg);
	exit(rt_error);
}

void	ft_error_dash(char *unknow)
{
	printf("%s '--%s'\n", D_ERR_MSG_UNRECO_OPTION, unknow);
	printf("%s\n", D_ERR_MSG_HELP);
	exit(2);
}

void	ft_error_option(char c)
{
	printf("%s --'%c'\n", D_ERR_MSG_INVALID_OPTION, c);
	printf("%s\n", D_ERR_MSG_HELP);
	exit(2);
}

void	ft_error_exist(char *str)
{
	printf("ls: cannot acces '%s': No such file or directory\n", str);
}

void	ft_error_access(char *str)
{
	printf("ls: cannot open directory '%s': Permission denied\n", str);
}
