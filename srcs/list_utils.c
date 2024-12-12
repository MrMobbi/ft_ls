
#include "../incl/ft_ls.h"

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

t_path	*ft_lst_path_new(char *str)
{
	t_path	*nw = malloc(sizeof(t_path));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	nw->folder = false;
	nw->next = NULL;
	nw->file = NULL;
	struct stat	s;
	if (stat(nw->name, &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
		{
			DIR				*p_dir;
			struct dirent	*p_dirent;
			p_dir = opendir(nw->name); //DIR
			nw->folder = true;
			if (p_dir == NULL)
				ft_error("opendir failled\n", 2); // todo proper message error
			while ((p_dirent = readdir(p_dir)) != NULL)
			{
				if (nw->file == NULL)
					nw->file = ft_lst_file_new(p_dirent->d_name, nw->name);
				else
					ft_lst_file_add(nw->file, ft_lst_file_new(p_dirent->d_name, nw->name));
			}
			closedir(p_dir);
		}
	}
	else
		ft_error_path(str);
	
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
		free(start);
		start = node;
	}
}

t_file	*ft_lst_file_new(char *name, char *dir)
{
	t_file	*nw = malloc(sizeof(t_file));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(name);
	nw->path = ft_str_join_path(dir, name);
	nw->next = NULL;
	struct stat	s;
	if (stat(nw->path, &s) == 0)
	{
		if (S_ISREG(s.st_mode) && (s.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
			nw->type = E_EXEC; // check if the bit is exec and a file
		else if (S_ISREG(s.st_mode))
			nw->type = E_FILE;
		else if (S_ISDIR(s.st_mode)) // check the bit from a macro
			nw->type = E_DIR;
		else
		{
			printf("here\n");
			printf("%s | %d", strerror(errno), errno);;
			exit(3); // todo proper error handling
		}
		if (nw->name[0] == '.')
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
