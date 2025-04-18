
#include "../incl/ft_ls.h"

/* Print the error message and return the code status */
void	ft_error(char *msg, int rt_error)
{
	perror(msg);
	exit(rt_error);
}

/* Print an error message because there is too much '-' */
void	ft_error_dash(char *unknow)
{
	printf("%s '--%s'\n", D_ERR_MSG_UNRECO_OPTION, unknow);
	printf("%s\n", D_ERR_MSG_HELP);
	exit(2);
}

/* Print an error message because option is not vaild */
void	ft_error_option(char c)
{
	printf("%s -- '%c'\n", D_ERR_MSG_INVALID_OPTION, c);
	printf("%s\n", D_ERR_MSG_HELP);
	exit(2);
}
