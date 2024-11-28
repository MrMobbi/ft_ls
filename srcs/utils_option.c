
#include "../incl/ft_ls.h"

void	ft_option_check_dash(char *str)
{
	int dash = 0;
	while (*str == '-' && dash < 2)
	{
		dash++;
		str++;
	}
	if (dash == 2 && ft_str_cmp(str, "help"))
		ft_print_help();
	else if (dash > 1)
		ft_error_dash(str);

}

void	ft_option_check_error(char c)
{
	char	*option = D_ALL_OPTION;
	size_t	len = ft_strlen(option);
	for (size_t i = 0; i < len; i++)
	{
		if (option[i] == c)
			return ;
	}
	ft_error_option(c);
}

static bool	ft_option_not_seen(char *str, char c)
{
	if (str == NULL)
		return (true);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == c)
			return (false);
	}
	return (true);
}

static char	*ft_option_join(char *str, char c)
{
	int		i = 0;
	char	*nw = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	if (str == NULL)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
		str[0] = c;
		str[1] = '\0';
		return str;
	}
	while (str[i] != '\0')
	{
		nw[i] = str[i];
		i++;
	}
	nw[i] = c;
	nw[i + 1] = '\0';
	free(str);
	return (nw);
}

char	*ft_option_add(char *option, char *add)
{
	while (*add == '-')
		add++;
	for (int i = 0; add[i] != '\0'; i++)
	{
		ft_option_check_error(add[i]);
		if (ft_option_not_seen(option, add[i]))
			option = ft_option_join(option, add[i]);
	}
	return (option);
}
