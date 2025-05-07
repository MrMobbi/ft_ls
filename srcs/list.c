
#include "../incl/ft_ls.h"

// #################
// ###   TOKEN   ###
// #################

t_token	*ft_lst_token_new(char *str)
{
	t_token	*nw = malloc(sizeof(t_token));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	nw->next = NULL;
	nw->option = false;
	if (str[0] == '-')
		nw->option = true;
	return (nw);
}

void	ft_lst_token_add(t_token *ptr, t_token *nw)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = nw;
}

void	ft_lst_token_free(t_token *ptr)
{
	t_token	*tmp;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

// ################
// ###   PATH   ###
// ################

t_path	*ft_lst_path_new(char *str, t_option option)
{
	t_path	*nw = malloc(sizeof(t_path));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	nw->folder = false;
	nw->link = false;
	nw->error = 0;
	nw->next = NULL;
	nw->file = NULL;
	nw->extand = NULL;

	struct stat	st;
	if (lstat(nw->name, &st) != 0)
	{
		if (errno == ENOENT)
		{
			nw->error = E_ERR_EXIST;
			return (nw);
		}
		else
			ft_error(str, errno);
	}
	nw->time = st.st_mtime;
	if (option.long_listing)
	{
		nw->extand = malloc(sizeof(t_long));
		if (!nw->extand)
			ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
		nw->extand->time = nw->time;
		nw->extand->mode = st.st_mode;
		nw->extand->nlink = st.st_nlink;
		nw->extand->uid = st.st_uid;
		nw->extand->gid = st.st_gid;
		nw->extand->size = st.st_size;
	}
	if (S_ISDIR(st.st_mode))
	{
		DIR				*p_dir;
		struct dirent	*p_dirent;
		nw->folder = true;
		p_dir = opendir(nw->name);
		if (p_dir == NULL)
		{
			if (errno == EACCES)
				nw->error = E_ERR_ACCESS;
		}
		else 
		{
			while ((p_dirent = readdir(p_dir)) != NULL)
			{
				if (option.hidden || p_dirent->d_name[0] != '.')
				{
					t_file	*new_file = ft_lst_file_new(p_dirent->d_name, nw->name, option.long_listing);
					if (nw->file == NULL)
						nw->file = new_file;
					else
						ft_lst_file_add(nw->file, new_file);
				}
			}
			closedir(p_dir);
		}	
	}
	return (nw);
}

void	ft_lst_path_add(t_path *ptr, t_path *nw)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = nw;
}

void	ft_lst_path_free(t_path *ptr)
{
	t_path	*tmp;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr->name);
		if (ptr->folder == true)
			ft_lst_file_free(ptr->file);
		if (ptr->extand)
			free(ptr->extand);
		free(ptr);
		ptr = tmp;
	}
}

// ################
// ###   FILE   ###
// ################

t_file	*ft_lst_file_new(char *name, char *dir, bool long_listing)
{
	t_file	*nw = malloc(sizeof(t_file));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(name);
	nw->path = ft_str_join_path(dir, name);
	nw->next = NULL;
	nw->extand = NULL;
	struct stat	s;
	if (lstat(nw->path, &s) == 0)
	{
		nw->time = s.st_mtime;
		if (long_listing)
		{
			nw->extand = malloc(sizeof(t_long));
			if (!nw->extand)
				ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
			nw->extand->time = nw->time;
			nw->extand->mode = s.st_mode;
			nw->extand->nlink = s.st_nlink;
			nw->extand->uid = s.st_uid;
			nw->extand->gid = s.st_gid;
			nw->extand->size = s.st_size;
		}
		if (S_ISDIR(s.st_mode))
			nw->type = E_FOLDER;
		else
			nw->type = E_OTHER;
		if (!ft_str_cmp(nw->name, "."))
			nw->type = E_CURRENT;
		else if (!ft_str_cmp(nw->name, ".."))
			nw->type = E_PREVIOUS;
	}
	else
		ft_error(name, errno);
	return (nw);
}

void	ft_lst_file_add(t_file *ptr, t_file *nw)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = nw;
}

void	ft_lst_file_free(t_file *ptr)
{
	t_file	*tmp;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr->name);
		free(ptr->path);
		if (ptr->extand)
			free(ptr->extand);
		free(ptr);
		ptr = tmp;
	}
}
