
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

char	*ft_str_join_path(char *start, char *file)
{
	char	*path = malloc(sizeof(char) * (ft_strlen(start) + \
										   ft_strlen(file) + 2));
	if (!path)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	size_t	current = 0;
	for (size_t i = 0; i < ft_strlen(start); i++)
	{
		path[current] = start[i];
		current++;
	}
	path[current++] = '/';
	for (size_t i = 0; i < ft_strlen(file); i++)
	{
		path[current] = file[i];
		current++;
	}
	path[current] = '\0';
	return (path);
}

int	ft_str_cmp(char *str1, char *str2)
{
	int	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return ((int)(str1[i] - str2[i]));
		i++;
	}
	return ((int)(str1[i] - str2[i]));
}

static char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int	ft_str_cmp_case(char *str1, char *str2)
{
	int	i = 0;
	char	c1;
	char	c2;
	while (str1[i] != '\0')
	{
		c1 = to_lower(str1[i]);
		c2 = to_lower(str2[i]);
		if (c1 != c2)
			return ((int)(c1 - c2));
		i++;
	}
	c1 = to_lower(str1[i]);
	c2 = to_lower(str2[i]);
	return ((int)(c1 - c2));
}
