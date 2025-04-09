
#include "../incl/ft_ls.h"

void	ft_apply_recursive(t_path *path)
{
	t_path	*node = path;
	while (node != NULL)
	{
		t_file	*file = node->file;
		while (file != NULL)
		{
			if (file->type == E_DIR)
				ft_lst_path_add_here(node, ft_lst_path_new(file->path));
			file = file->next;
		}
		node = node->next;
	}
}

void	ft_apply_time(t_ls *ls)
{
	(void) ls;
}
