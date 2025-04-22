
#include "../incl/ft_ls.h"

/* Check the number of dash given as token */
static void	ft_option_check_dash(char *str)
{
	int dash = 0;
	while (*str == '-' && dash < 2)
	{
		str++;
		dash++;
	}
	if (dash == 2 && ft_str_cmp(str, "help") == 0)
		ft_print_help();
	else if (dash > 1)
		ft_error_dash(str);
}

/* Check if the option given is a valid option */
void	ft_option_check_error(char c)
{
	char	*option = D_ALL_OPTION;
	size_t	len = ft_strlen(option);
	for (size_t i = 0; i < len; i++)
	{
		if (option[i] == c)
			return ;
	}
	ft_error_option(c);
}

/* Check if the option is already seen */
static bool	ft_option_not_seen(char *str, char c)
{
	if (str == NULL)
		return (true);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == c)
			return (false);
	}
	return (true);
}

/* Will add the previous option with the new option found */
static char	*ft_option_join(char *str, char c)
{
	int		i = 0;
	char	*nw = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!nw)
		ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
	if (str == NULL)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			ft_error(D_ERR_MSG_MALLOC, E_ERR_MALLOC);
		str[0] = c;
		str[1] = '\0';
		return str;
	}
	while (str[i] != '\0')
	{
		nw[i] = str[i];
		i++;
	}
	nw[i] = c;
	nw[i + 1] = '\0';
	free(str);
	return (nw);
}

/* Will check if the option already exist in the string
 * where the option is stored for the main struct, 
 * if not the option is added to the string */
static char	*ft_option_add(char *option, char *add)
{
	while (*add == '-')
		add++;
	for (int i = 0; add[i] != '\0'; i++)
	{
		ft_option_check_error(add[i]);
		if (ft_option_not_seen(option, add[i]))
			option = ft_option_join(option, add[i]);
	}
	return (option);
}

/* Will iterate in the list of token to get the option
 * and initiate a string with all the valid option */
char	*ft_option_get(t_token *ptr)
{
	char	*option = NULL;
	while (ptr != NULL)
	{
		if (ptr->option)
		{
			ft_option_check_dash(ptr->name);
			option = ft_option_add(option, ptr->name);
		}
		ptr = ptr->next;
	}
	return (option);
}

/* */
void	ft_option_file_sort_alpha(t_file **head)
{
	bool	swapped;
	t_file	*ptr;
	t_file	*prev;
	t_file	*tmp;

	if (head == NULL || *head == NULL)
		return ;

	do {
		swapped = false;
		ptr = *head;
		prev = NULL;

		while (ptr != NULL && ptr->next != NULL)
		{
			if (ft_strcmp_special(ptr->name, ptr->next->name) > 0)
			{
				tmp = ptr->next;
				ptr->next = tmp->next;
				tmp->next = ptr;
				if (prev == NULL)
					*head = tmp;
				else
					prev->next = tmp;
				swapped = true;
				prev = tmp;
			}
			else
			{
				prev = ptr;
				ptr = ptr->next;
			}
		}
	}
	while (swapped);
}

/* this function rearange order of the token in an alphabetic order */
void ft_rearrange_alpha(t_ls *ls)
{
	t_path	*node = ls->path;
	t_path	*file_head = NULL;
	t_path	*file_node = NULL;
	t_path	*folder_head = NULL;
	t_path	*folder_node = NULL;
	while (node != NULL)
	{
		if (node->folder == true)
		{
			ft_option_file_sort_alpha(&node->file);
			if (folder_head == NULL)
			{
				folder_node = node;
				folder_head = folder_node;
			}
			else
			{
				folder_node->next = node;
				folder_node = folder_node->next;
			}
		}
		else
		{
			if (file_head == NULL)
			{
				file_node = node;
				file_head = file_node;
			}
			else
			{
				file_node->next = node;
				file_node = file_node->next;
			}
		}
		node = node->next;
	}
	if (file_node)
		file_node->next = NULL;
	if (folder_node)
		folder_node->next = NULL;
	ft_path_sort_alpha(&file_head);
	ft_path_sort_alpha(&folder_head);
	if (file_node != NULL)
	{
		file_node = file_head;
		while (file_node->next != NULL)
			file_node = file_node->next;
		if (file_node != NULL)
			file_node->next = folder_head;
	}
	ls->path = (file_head != NULL) ? file_head : folder_head;
}
