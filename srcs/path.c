
#include "../incl/ft_ls.h"

/* Will itarate trough the list of token and get all 
 * path given by the prompt */
t_path	*ft_path_get(t_token *ptr)
{
	t_path	*path = NULL;
	while (ptr != NULL)
	{
		if (!ptr->option)
		{
			t_path	*new_path = ft_lst_path_new(ptr->name);
			if (path == NULL)
				path = new_path;
			else
				ft_lst_path_add(path, new_path);
		}
		ptr = ptr->next;
	}
	return (path);
}


void	ft_path_sort_alpha(t_path **head)
{
	bool	swapped;
	t_path	*ptr;
	t_path	*prev;
	t_path	*tmp;

	if (head == NULL || *head == NULL)
		return ;

	do {
		swapped = false;
		ptr = *head;
		prev = NULL;

		while (ptr != NULL && ptr->next != NULL)
		{
			if (ft_strcmp_special(ptr->name, ptr->next->name) > 0)
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
	}
	while (swapped);
}
