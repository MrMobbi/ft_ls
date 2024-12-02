
#include "../incl/ft_ls.h"

t_token	*ft_lst_token_new(char *str)
{
	t_token	*nw = malloc(sizeof(t_token));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	nw->option = false;
	nw->path = false;
	if (str[0] == '-')
		nw->option = true;
	else
		nw->path = true;
	nw->next = NULL;
	return (nw);
}

void	ft_lst_token_add(t_token *start, t_token *nw)
{
	t_token	*node = start;
	if (node->next == NULL)
		node->next = nw;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = nw;
	}
}

t_path	*ft_lst_path_new(char *str)
{
	t_path	*nw = malloc(sizeof(t_path));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->file = false;
	nw->name = ft_str_dup(str);
	struct stat	s;
	if (stat(nw->name, &s) == 0)
	{
		if (S_ISREG(s.st_mode))
			nw->file = true;
		else if (S_ISDIR(s.st_mode))
		{
			nw->p_dir = opendir(nw->name); //DIR
			if (nw->p_dir == NULL)
				ft_error("opendir failled\n", 2); // todo proper message error
		}
	}
	else
		ft_error_path(str);
	return (nw);
}

void	ft_lst_path_add(t_path *start, t_path *nw)
{
	t_path	*node = start;
	if (node->next == NULL)
		node->next = nw;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = nw;
	}
}
/*
    // Process each entry.

    while ((pDirent = readdir(pDir)) != NULL) {
		printf ("[%s]\n", pDirent->d_name);
    }

    // Close directory and exit.

	closedir (pDir);
	*/
