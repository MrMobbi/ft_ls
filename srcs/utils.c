
#include "../incl/ft_ls.h"

size_t	ft_strlen(char *str)
{
	int	length = 0;
	if (str == NULL)
		return (0);
	while (str[length] != '\0')
		length++;
	return (length);
}

char	*ft_str_dup(char *str)
{
	char	*new = malloc(ft_strlen(str) + 1);
	if (!new)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	for (size_t i = 0; i < ft_strlen(str); i++)
		new[i] = str[i];
	new[ft_strlen(str)] = '\0';
	return (new);
}

bool	ft_str_cmp(char *str1, char *str2)
{
	int	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return false;
		i++;
	}
	if (str1[i] != str2[i])
		return false;
	return true;
}

char	*ft_str_join(char *str1, char *str2)
{
	char	*nw = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	size_t current = 0;
	for (size_t i = 0; i < ft_strlen(str1); i++)
	{
		nw[current] = str1[i];
		current++;
	}
	for (size_t i = 0; i < ft_strlen(str2); i++)
	{
		nw[current] = str2[i];
		current++;
	}
	nw[current] = '\0';
	return nw;
}
