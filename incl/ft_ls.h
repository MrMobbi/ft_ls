
#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>

//	ERROR MSG
# define D_ERR_MSG_MALLOC			"Malloc failled"
# define D_ERR_MSG_UNRECO_OPTION	"ls: unrecognized option:"
# define D_ERR_MSG_INVALID_OPTION	"ls: invalide option:"
# define D_ERR_MSG_HELP				"Try 'ls --help' for mode information"

// OTHER MSG
# define D_DEFAULT_PATH		"."
# define D_ALL_OPTION		"lartR"

enum e_error{
	E_ERR_MALLOC = 1,
	E_ERR_EXIT = 2,
};

typedef struct s_token {
	char	*name;
	bool	option;
	bool	path;
	struct s_token	*next;
}	t_token;

typedef struct s_path {
	char	*name;
	DIR		*dr;
	struct dirent	*de;
	struct s_path	*next;
}	t_path;

typedef struct s_ls {
	char	*option;
	struct s_path	*path;
	struct s_token	*token;
}	t_ls;

// init_main_struct
void	ft_init_main_struct(t_ls *ls, int ac, char **av);

// utils_list
t_token	*ft_lst_token_new(char *str);
void	ft_lst_token_add(t_token *start, t_token *nw);

// utils_option
void	ft_option_check_dash(char *str);
char	*ft_option_add(char *option, char *add);

// utils
size_t	ft_strlen(char *str);
char	*ft_str_dup(char *str);
bool	ft_str_cmp(char *str1, char *str2);

// exit
void	ft_error(char *msg, int rt_error);
void	ft_error_dash(char *unknow);
void	ft_error_option(char c);

// print
void	ft_print(t_ls *ls);
void	ft_print_help(void);

// debug
void	db_print_token(t_token *token);

#endif
