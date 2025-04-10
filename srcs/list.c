
#include "../incl/ft_ls.h"

// ################
// ###	TOKEN	###
// ################

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
void	ft_lst_token_add(t_token *start, t_token *nw)
{
	t_token	*node = start;
	while (node->next != NULL)
		node = node->next;
	node->next = nw;
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
