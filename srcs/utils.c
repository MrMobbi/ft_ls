
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
		ft_error(D_ERR_MSG_MALLOC);
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
		ft_error(D_ERR_MSG_MALLOC);
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
	t_cmp	cmp_a, cmp_b;

	switch (type_cmp) {
		case  TYPE_FILE:
			cmp_a.file = (t_file *) a;
			cmp_b.file = (t_file *) b;
			str1 = cmp_a.file->name;
			str2 = cmp_b.file->name;
			break ;
		case TYPE_PATH:
			cmp_a.path = (t_path *) a;
			cmp_b.path = (t_path *) b;
			str1 = cmp_a.path->name;
			str2 = cmp_b.path->name;
			break ;
		default:
			ft_error("Error cmp alpha");
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
	t_cmp	cmp_a, cmp_b;
	switch (type_cmp) {
		case  TYPE_FILE:
			cmp_a.file = (t_file *)a;
			cmp_b.file = (t_file *)b;
			time_a = cmp_a.file->time;
			time_b = cmp_b.file->time;
			break ;
		case TYPE_PATH:
			cmp_a.path = (t_path *)a;
			cmp_b.path = (t_path *)b;
			time_a = cmp_a.path->time;
			time_b = cmp_b.path->time;
			break ;
		default:
			ft_error("Error cmp time");
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

static void	*ft_file_next_get(void *ptr)
{ return (((t_file *)ptr)->next); }

static void	*ft_path_next_get(void *ptr)
{ return (((t_path *)ptr)->next); }

static void	ft_file_next_set(void *ptr, void *next)
{ ((t_file *)ptr)->next = (t_file *)next; }

static void	ft_path_next_set(void *ptr, void *next)
{ ((t_file *)ptr)->next = (t_file *)next; }

typedef int (*t_cmp_func)(const void *, const void *, compare_type);
typedef void *(*t_get_next_func)(void *);
typedef void (*t_set_next_func)(void *, void *);
void	*ft_reverse(void *head, bool file)
{
	t_get_next_func next_get = file ? ft_file_next_get : ft_path_next_get;
	t_set_next_func next_set = file ? ft_file_next_set : ft_path_next_set;
	void *prev = NULL;
	void *curr = head;
	void *next = NULL;

	while (curr)
	{
		next = next_get(curr);
		next_set(curr, prev);
		prev = curr;
		curr = next;
	}
	return (prev);
}

void	*ft_swap(void *head, t_option option, bool file)
{
	t_cmp_func cmp = option.time ? ft_cmp_time : ft_cmp_alpha;
	t_get_next_func next_get = file ? ft_file_next_get : ft_path_next_get;
	t_set_next_func next_set = file ? ft_file_next_set : ft_path_next_set;
	void	*ptr, *tmp, *prev;
	bool	swapped;
	do {
		swapped = false;
		ptr = head;
		prev = NULL;

		while (ptr != NULL && next_get(ptr) != NULL)
		{
			if (cmp(ptr, next_get(ptr), TYPE_FILE) > 0)
			{
				tmp = next_get(ptr);
				next_set(ptr, next_get(tmp));
				next_set(tmp, ptr);
				if (prev == NULL)
					head = tmp;
				else
					next_set(prev, tmp);
				swapped = true;
				prev = tmp;
			}
			else
			{
				prev = ptr;
				ptr = next_get(ptr);
			}
		}
	} while (swapped);
	if (option.reverse)
		head = ft_reverse(head, file);
	return (head);
}
