

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
# include <stdarg.h>

//	#############################
//	####   DEFINE AND ENUM   ####
//	#############################

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
	E_FOLDER = 1,
	E_HIDE = 2,
	E_OTHER = 3,
	E_CURRENT = 4,
	E_PREVIOUS = 5,
};

//	##################
//	####   LIST   ####
//	##################

typedef struct	s_ls {
	int		return_status;
	char	*option;
	struct s_path	*path;
}	t_ls;

typedef struct s_token {
	char	*name;
	bool	option;
	struct s_token	*next;
}	t_token;

typedef struct	s_path {
	char	*name;
	bool	folder;
	int		error;
	time_t	time;
	struct s_file	*file;
	struct s_path	*next;
}	t_path;

typedef struct	s_file {
	char	*name;
	char	*path;
	int		type;
	time_t	time;
	struct s_file	*next;
}	t_file;

//	######################
//	####   FUNCTION   ####
//	######################

//	### DEBUG ###
void	db_print_token(t_token *ptr);
void	db_print_path(t_path *ptr);
void	db_print_file(t_file *ptr);

//	### ERROR ###
void	ft_error(char *msg, int rt_error);
void	ft_error_dash(char *unknow);
void	ft_error_option(char c);

//	### EXTRACT ###
void	ft_extract_path_and_option(int ac, char **av, t_ls *ls);

//	### LIST ###
t_token	*ft_lst_token_new(char *str);
void	ft_lst_token_add(t_token *ptr, t_token *nw);
void	ft_lst_token_free(t_token *ptr);
t_path	*ft_lst_path_new(char *str);
void	ft_lst_path_add(t_path *ptr, t_path *nw);
void	ft_lst_path_free(t_path *ptr);
t_file	*ft_lst_file_new(char *name, char *dir);
void	ft_lst_file_add(t_file *ptr, t_file *nw);
void	ft_lst_file_free(t_file *ptr);

//	### OPTION ###
char	*ft_option_get(t_token *ptr);
void	ft_option_file_sort_alpha(t_file **head);

//	### PATH ###
t_path	*ft_path_get(t_token *ptr);
void	ft_path_sort_alpha(t_path **head);

//	### PRINT ###
void	ft_print_help(void);

//	### PRINTF ###
int		ft_printf(const char *str, ...);

//	### UTILS ###
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_put_unsinbr(unsigned int n);
int		ft_putnbr(int n);
size_t	ft_putnbr_size_t(size_t n);
size_t	ft_strlen(char *str);
char	*ft_str_dup(char *str);
int		ft_str_cmp(char *str1, char *str2);
char	*ft_str_join_path(char *start, char *file);
int		ft_str_cmp_case(char *str1, char *str2);

#endif
