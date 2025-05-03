
#include "../incl/ft_ls.h"

typedef int (*t_cmp_func)(const void *, const void *, compare_type);

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

static char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int	ft_cmp_alpha(const void *a, const void *b, compare_type type_cmp)
{
	int		i = 0;
	char	c1, c2;
	char *str1;
	char *str2;

	switch (type_cmp) {
		case  TYPE_FILE:
			t_file	*fa = (t_file *) a;
			t_file	*fb = (t_file *) b;
			str1 = fa->name;
			str2 = fb->name;
			break ;
		case TYPE_PATH:
			t_path	*pa = (t_path *) a;
			t_path	*pb = (t_path *) b;
			str1 = pa->name;
			str2 = pb->name;
			break ;
		default:
			ft_error("Error cmp alpha", 3);
	}
	if (ft_str_cmp(str1, "..") == 0 && ft_str_cmp(str2, ".") == 0)
		return (1);
	while (*str1 != '\0')
	{
		if (*str1 == '.')
			str1++;
		else
			break;
	}
	while (*str2 != '\0')
	{
		if (*str2 == '.')
			str2++;
		else
			break;
	}
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

int ft_cmp_time(const void *a, const void *b, compare_type type_cmp)
{
	time_t	time_a, time_b;
	switch (type_cmp) {
		case  TYPE_FILE:
			const t_file *fa = (const t_file *) a;
			const t_file *fb = (const t_file *) b;
			time_a = fa->time;
			time_b = fb->time;
			break ;
		case TYPE_PATH:
			const t_path *pa = (const t_path *) a;
			const t_path *pb = (const t_path *) b;
			time_a = pa->time;
			time_b = pb->time;
			break ;
		default:
			ft_error("Error cmp time", 3);
	}
	if (time_a == time_b)
		return (ft_cmp_alpha(a, b, type_cmp));
	return ((time_a < time_b) ? 1 : 0);
}

bool	ft_is_option(char c, char *option)
{
	if (option == NULL)
		return false;
	while (*option != '\0')
	{
		if (*option == c)
			return true;
		option++;
	}
	return false;
}

t_file	*ft_swap_file(t_file *head, bool sort_by_time);
t_path	*ft_swap_path(t_path *head, bool sort_by_time);
void ft_sort_type(void **head, bool sort_by_time, compare_type type_cmp)
{
	if (!head || !*head)
		return;

	switch (type_cmp)
	{
		case TYPE_FILE:
			*head = ft_swap_file((t_file*) *head, sort_by_time);
			break ;
		case TYPE_PATH:
			*head = ft_swap_path((t_path*) *head, sort_by_time);
			break ;
		default:
			ft_error("error cmp", 3);
	}
}

t_file	*ft_swap_file(t_file *head, bool sort_by_time)
{
	t_cmp_func cmp = sort_by_time ? ft_cmp_time : ft_cmp_alpha;
	t_file	*ptr, *tmp, *prev;
	bool	swapped;
	do {
		swapped = false;
		ptr = head;
		prev = NULL;

		while (ptr != NULL && ptr->next != NULL)
		{
			if (cmp(ptr, ptr->next, TYPE_FILE) > 0)
			{
				tmp = ptr->next;
				ptr->next = tmp->next;
				tmp->next = ptr;
				if (prev == NULL)
					head = tmp;
				else
					prev->next = tmp;
				swapped = true;
				prev = tmp;
			}
			else
			{
				prev = ptr;
				ptr = ptr->next;
			}
		}
	} while (swapped);
	return (head);
}

t_path	*ft_swap_path(t_path *head, bool sort_by_time)
{
	t_cmp_func cmp = sort_by_time ? ft_cmp_time : ft_cmp_alpha;
	t_path	*ptr, *tmp, *prev;
	bool	swapped;
	do {
		swapped = false;
		ptr = head;
		prev = NULL;

		while (ptr != NULL && ptr->next != NULL)
		{
			if (cmp(ptr, ptr->next, TYPE_PATH) > 0)
			{
				tmp = ptr->next;
				ptr->next = tmp->next;
				tmp->next = ptr;
				if (prev == NULL)
					head = tmp;
				else
					prev->next = tmp;
				swapped = true;
				prev = tmp;
			}
			else
			{
				prev = ptr;
				ptr = ptr->next;
			}
		}
	} while (swapped);
	return (head);
}
