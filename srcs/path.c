
#include "../incl/ft_ls.h"

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

void	ft_path_rearrange(t_ls *ls, t_option option)
{
	t_path	*node = ls->path;
	t_path	*file_head = NULL, *file_tail = NULL;
	t_path	*error_head = NULL, *error_tail = NULL;
	t_path	*folder_head = NULL, *folder_tail = NULL;
	while (node != NULL)
	{
		t_path *next = node->next;
		node->next = NULL;
		if (node->folder)
		{
			node->file = ft_swap(node->file, option, false);
			if (!folder_head)
				folder_head = folder_tail = node;
			else
				folder_tail = folder_tail->next = node;
		}
		else if (node->error == E_ERR_EXIST)
		{
			if (!error_head)
				error_head = error_tail = node;
			else
				error_tail = error_tail->next = node;
		}
		else
		{
			if (!file_head)
				file_head = file_tail = node;
			else
				file_tail = file_tail->next = node;
		}
		node = next;
	}
	file_head = ft_swap(file_head, option, false);
	error_head = ft_swap(error_head, option, false);
	folder_head = ft_swap(folder_head, option, false);
	if (error_head)
	{
		error_tail = error_head;
		while (error_tail->next != NULL)
			error_tail = error_tail->next;
		error_tail->next = file_head;
	}
	if (file_head)
	{
		file_tail = file_head;
		while (file_tail->next != NULL)
			file_tail = file_tail->next;
		file_tail->next = folder_head;
	}
	ls->path = error_head ? error_head : (file_head ? file_head : folder_head);
}
