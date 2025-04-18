
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

// OTHER DEFINE
# define D_DEFAULT_PATH		"."
# define D_ALL_OPTION		"lartR"

// COLORS
# define D_RED		"\033[31m"
# define D_GREEN	"\033[32m"
# define D_BLUE		"\033[34m"
# define D_MAGENTA	"\033[35m"
# define D_CYAN		"\033[36m"
# define D_RESET	"\033[0m"


// the C mean if letter is capital
enum e_option {
	E_OPTION_CR = 82,
	E_OPTION_A = 97,
	E_OPTION_L = 108,
	E_OPTION_R = 114,
	E_OPTION_T = 116,
};

enum e_error{
	E_ERR_MALLOC = 1,
	E_ERR_EXIT = 2,
	E_ERR_ACCESS = 3,
	E_ERR_EXIST = 4,
};

enum e_file_type {
	E_FILE = 1,
	E_DIR = 2,
	E_EXEC = 3,
	E_CURRENT = 14,
	E_PREVIOUS = 15,
	E_FILE_HIDE = 11,
	E_DIR_HIDE = 12,
	E_EXEC_HIDE = 13,
};

//	main data struct
typedef struct s_ls {
	char	*option;
	int		nb_to_print;
	bool	recur;
	struct s_token	*token;
	struct s_path	*path;
}	t_ls;

// tokenizing the args
typedef struct s_token {
	char	*name;
	bool	option;
	bool	path;
	struct s_token	*next;
}	t_token;

// path to the file or the directory
typedef struct s_path {
	char	*name;
	bool	folder;
	int		error;
	time_t	time;
	struct s_file	*file; // <- if folder this is the chain list to files in it
	struct s_path	*next;
}	t_path;

// files that are in the directory
typedef struct s_file {
	char	*name;
	char	*path;
	int		type;
	time_t	time;
	struct s_file	*next;
}	t_file;

// init_main_struct
void	ft_init_main_struct(t_ls *ls, int ac, char **av);

// utils_list
t_token	*ft_lst_token_new(char *str);
void	ft_lst_token_add(t_token *start, t_token *nw);
void	ft_lst_token_free(t_token *start);
t_path	*ft_lst_path_new(char *str);
void	ft_lst_path_add(t_path *start, t_path *nw);
void	ft_lst_path_add_here(t_path *here, t_path *nw);
void	ft_lst_path_free(t_path *start);
t_file	*ft_lst_file_new(char *name, char *dir);
void	ft_lst_file_add(t_file *start, t_file *nw);
void	ft_lst_file_free(t_file *start);

// option_utils
void	ft_option_check_dash(char *str);
char	*ft_option_add(char *option, char *add);
bool	ft_option_checker(char *str, char c);
void	ft_option_path_sort_alpha(t_path **head);
void	ft_option_file_sort_alpha(t_file **head);

// option_apply
void	ft_apply_recursive(t_path	*start);
void	ft_apply_time(t_ls *ls);

// utils
size_t	ft_strlen(char *str);
char	*ft_str_dup(char *str);
char	*ft_str_join(char *str1, char *str2);
char	*ft_str_join_path(char *start, char *file);
int		ft_str_cmp(char *str1, char *str2);
int		ft_str_cmp_case(char *str1, char *str2);

// error
void	ft_error(char *msg, int rt_error);
void	ft_error_dash(char *unknow);
void	ft_error_option(char c);
void	ft_error_exist(char *str);
void	ft_error_access(char *str);

// print
void	ft_print(t_ls ls);
void	ft_print_help(void);

// debug
void	db_print_ls(t_ls *ls);
void	db_print_file(t_file *file);
void	db_print_path(t_path *path);
void	db_print_token(t_token *toke);

#endif
