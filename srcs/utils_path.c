
#include "../incl/ft_ls.h"

char	*ft_path_check(char *str)
{
	char	*nw = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	if (str[0] == '/')
		return (str);

	return (nw);
}
