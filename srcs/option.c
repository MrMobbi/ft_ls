
#include "../incl/ft_ls.h"

static void	ft_option_check_dash(char *str)
{
	int dash = 0;
	while (*str == '-' && dash < 2)
	{
		str++;
		dash++;
	}
	if (dash == 2 && ft_str_cmp(str, "help") == 0)
	{
		ft_print_help();
		exit (0);
	}
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
		ft_error(D_ERR_MSG_MALLOC);
	if (str == NULL)
	{
		nw[0] = c;
		nw[1] = '\0';
		return (nw);
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

static char	*ft_option_add(char *option, char *add)
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

char	*ft_option_get(t_token *ptr)
{
	char	*option = NULL;
	while (ptr != NULL)
	{
		if (ptr->option)
		{
			ft_option_check_dash(ptr->name);
			option = ft_option_add(option, ptr->name);
		}
		ptr = ptr->next;
	}
	return (option);
}
