
#include "../incl/ft_ls.h"

// #################
// ###   TOKEN   ###
// #################

/* Create a new token and determinate if 
 * it an option or a path */
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

/* Add a new chain to the end of the list */
void	ft_lst_token_add(t_token *ptr, t_token *nw)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = nw;
}

/* Go trough the list and free all allocation */
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

/* Create a new path and determinate if the path is valid
 * and if the path is a folder or a file */
t_path	*ft_lst_path_new(char *str, bool hidden)
{
	t_path	*nw = malloc(sizeof(t_path));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	nw->folder = false;
	nw->next = NULL;
	nw->file = NULL;

	struct stat	st;
	if (lstat(nw->name, &st) != 0)
	{
		if (errno == ENOENT)
			nw->error = E_ERR_EXIST;
		else
			ft_error(str, errno);
	}
	nw->time = st.st_mtime;
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
				if (hidden || p_dirent->d_name[0] != '.')
				{
					t_file	*new_file = ft_lst_file_new(p_dirent->d_name, nw->name);
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
		free(ptr);
		ptr = tmp;
	}
}

// ################
// ###   FILE   ###
// ################

t_file	*ft_lst_file_new(char *name, char *dir)
{
	t_file	*nw = malloc(sizeof(t_file));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(name);
	nw->path = ft_str_join_path(dir, name);
	nw->next = NULL;
	struct stat	s;
	if (lstat(nw->path, &s) == 0)
	{
		nw->time = s.st_mtime;
		if (S_ISDIR(s.st_mode)) // directory check
			nw->type = E_FOLDER;
		else
			nw->type = E_OTHER;
		if (nw->name[0] == '.') // hide file check
			nw->type = E_HIDE;
		if (!ft_str_cmp(nw->name, "."))
			nw->type = E_CURRENT;
		else if (!ft_str_cmp(nw->name, ".."))
			nw->type = E_PREVIOUS;
	}
	else
	{
		printf("%s | %d", strerror(errno), errno);;
		exit(3); // todo proper exit
	}
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
		free(ptr);
		ptr = tmp;
	}
}
