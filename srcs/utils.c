
#include "../incl/ft_ls.h"

size_t	ft_putnbr_size_t(size_t n)
{
	static int	count;

	count = 0;
	if (n > 9)
	{
		ft_putnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_putnbr(int n)
{
	static int	count;
	int			neg;

	count = 0;
	neg = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		neg = 1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		count += ft_putchar(n + '0');
	if (neg == 1)
		count += 1;
	return (count);
}

int	ft_put_unsinbr(unsigned int n)
{
	static int	count;

	count = 0;
	if (n > 9)
	{
		ft_put_unsinbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_putstr(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

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
