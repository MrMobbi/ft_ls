
#include "../incl/ft_ls.h"

typedef int (*t_cmp_func)(t_path *, t_path *);

/* Will itarate trough the list of token and get all 
 * path given by the prompt */
t_path	*ft_path_get(t_token *ptr, bool hidden)
{
	t_path	*path = NULL;
	while (ptr != NULL)
	{
		if (!ptr->option)
		{
			t_path	*new_path = ft_lst_path_new(ptr->name, hidden);
			if (path == NULL)
				path = new_path;
			else
				ft_lst_path_add(path, new_path);
		}
		ptr = ptr->next;
	}
	return (path);
}

int cmp_alpha(t_path *a, t_path *b)
{
	return ft_strcmp_special(a->name, b->name);
}

int cmp_time(t_path *a, t_path *b)
{
	if (a->time == b->time)
		return cmp_alpha(a, b);
	return (a->time < b->time) ? 1 : -1;
}

void ft_path_sort(t_path **head, bool sort_by_time)
{
	t_cmp_func cmp = sort_by_time ? cmp_time : cmp_alpha;
	bool swapped;
	t_path *ptr, *prev, *tmp;

	if (!head || !*head)
		return;
	do {
		swapped = false;
		ptr = *head;
		prev = NULL;

		while (ptr != NULL && ptr->next != NULL)
		{
			if (cmp(ptr, ptr->next) > 0)
			{
				tmp = ptr->next;
				ptr->next = tmp->next;
				tmp->next = ptr;
				if (prev == NULL)
					*head = tmp;
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
}
