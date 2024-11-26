
#include "../incl/ft_ls.h"

t_file	*ft_list_new(struct dirent *de)
{
	t_file	*new = malloc(sizeof(t_file));
	if (!new)
		exit(1); // todo return function
	new->de = de;
	new->next = NULL;
	return (new);
}

void	ft_list_add(t_file *start, t_file *nw)
{
	t_file	*node = start;

	if (node->next == NULL)
		node->next = nw;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = nw;
	}
}

void	db_list_print(t_file *start)
{
	t_file	*node = start;
	while (node != NULL)
	{
		printf("[%s]\n length : %d | type : %d\n", \
				node->de->d_name, \
				node->de->d_reclen, \
				node->de->d_type);
		node = node->next;
	}
}
