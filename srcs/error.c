
#include "../incl/ft_ls.h"

void	ft_error(char *msg)
{
	perror(msg);
	exit(2);
}

void	ft_error_dash(char *unknow)
{
	printf("%s '--%s'\n", D_ERR_MSG_UNRECO_OPTION, unknow);
	printf("%s\n", D_ERR_MSG_HELP);
	exit(2);
}

void	ft_error_option(char c)
{
	printf("%s -- '%c'\n", D_ERR_MSG_INVALID_OPTION, c);
	printf("%s\n", D_ERR_MSG_HELP);
	exit(2);
}
