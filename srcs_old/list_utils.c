
#include "../incl/ft_ls.h"

//	##### TOKEN #####

t_token	*ft_lst_token_new(char *str)
{
	t_token	*nw = malloc(sizeof(t_token));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	nw->option = false;
	nw->path = false;
	nw->next = NULL;
	if (str[0] == '-')
		nw->option = true;
	else
		nw->path = true;
	return (nw);
}

void	ft_lst_token_add(t_token *start, t_token *nw)
{
	t_token	*node = start;
	while (node->next != NULL)
		node = node->next;
	node->next = nw;
}

void	ft_lst_token_free(t_token *start)
{
	t_token	*node;
	while (start != NULL)
	{
		node = start->next;
		free(start->name);
		free(start);
		start = node;
	}
}

//	###### PATH ######

t_path	*ft_lst_path_new(char *str)
{
	t_path	*nw = malloc(sizeof(t_path));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	nw->folder = false;
	nw->error = false;
	nw->next = NULL;
	nw->file = NULL;
	struct stat	s;
	if (stat(nw->name, &s) != 0)
	{
		if (errno == ENOENT)
			nw->error = E_ERR_EXIST;
		else
			ft_error(str, errno);
		return (nw);
	}
	nw->time = s.st_mtime;
	if (S_ISDIR(s.st_mode))
	{
		DIR				*p_dir;
		struct dirent	*p_dirent;
		nw->folder = true;
		p_dir = opendir(nw->name); //DIR
		if (p_dir == NULL)
		{
			if (errno == EACCES)
				nw->error = E_ERR_ACCESS;
		}
		else 
		{
			while ((p_dirent = readdir(p_dir)) != NULL)
			{
				t_file	*new_file = ft_lst_file_new(p_dirent->d_name, nw->name);
				if (nw->file == NULL)
					nw->file = new_file;
				else
					ft_lst_file_add(nw->file, new_file);
			}
			closedir(p_dir);
		}
	}
	return (nw);
}

void	ft_lst_path_add(t_path *start, t_path *nw)
{
	t_path	*node = start;
	while (node->next != NULL)
		node = node->next;
	node->next = nw;
}

void	ft_lst_path_add_here(t_path *here, t_path *nw)
{
	nw->next = here->next;
	here->next = nw;
}

void	ft_lst_path_free(t_path *start)
{
	t_path	*node;
	while (start != NULL)
	{
		node = start->next;
		free(start->name);
		if (start->file != NULL)
			ft_lst_file_free(start->file);
		free(start);
		start = node;
	}
}

//	###### FILE #####

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
			nw->type = E_DIR;
		if (nw->name[0] == '.') // hide file check
			nw->type += 10;
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

void	ft_lst_file_add(t_file *start, t_file *nw)
{
	t_file	*node = start;
	while (node->next != NULL)
		node = node->next;
	node->next = nw;
}

void	ft_lst_file_free(t_file *start)
{
	t_file	*node;
	while (start != NULL)
	{
		node = start->next;
		free(start->name);
		free(start->path);
		free(start);
		start = node;
	}
}
