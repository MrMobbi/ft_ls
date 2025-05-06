
#include "../incl/ft_ls.h"

/* Will itarate trough the list of token and get all 
 * path given by the prompt */
t_path	*ft_path_get(t_token *ptr, bool hidden, bool long_listing)
{
	t_path	*path = NULL;
	t_option	option;

	option.hidden = hidden;
	option.long_listing = long_listing;
	while (ptr != NULL)
	{
		if (!ptr->option)
		{
			t_path	*new_path = ft_lst_path_new(ptr->name, option);
			if (path == NULL)
				path = new_path;
			else
				ft_lst_path_add(path, new_path);
		}
		ptr = ptr->next;
	}
	return (path);
}
