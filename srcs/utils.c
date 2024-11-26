
#include "../incl/ft_ls.h"

size_t	ft_strlen(char *str)
{
	int	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

char	*ft_dup(char *str)
{
	char	*new = malloc(ft_strlen(str) + 1);
	
	if (!new)
		exit(1); // todo exit function
	for (size_t i = 0; i < ft_strlen(str); i++)
		new[i] = str[i];
	new[ft_strlen(str)] = '\0';
	return (new);
}
