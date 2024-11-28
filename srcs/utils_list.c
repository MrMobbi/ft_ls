
#include "../incl/ft_ls.h"

t_token	*ft_lst_token_new(char *str)
{
	t_token	*nw = malloc(sizeof(t_token));
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	nw->name = ft_str_dup(str);
	if (!nw->name)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
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
