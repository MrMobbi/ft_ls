
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
			t_path	*nw = ft_lst_path_new(ptr->name);
			if (path == NULL)
				path = nw;
			else
				ft_lst_path_add(path, nw);
		}
		ptr = ptr->next;
	}
	return (path);
}
