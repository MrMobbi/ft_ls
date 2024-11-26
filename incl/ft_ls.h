
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

typedef struct s_file {
	struct dirent	*de;
	struct s_file	*next;
}	t_file;

typedef struct s_ls {
	char			*path;
	DIR				*dir;
	struct s_file	*start;
}	t_ls;

t_ls	*ft_init_main_struct(int ac, char **av);

// utils_list
t_file	*ft_list_new(struct dirent *de);
void	ft_list_add(t_file *start, t_file *nw);
void	db_list_print(t_file *start);

// utils
size_t	ft_strlen(char *str);
char	*ft_dup(char *str);

// exit
void	ft_exit(t_ls *ls);

// print
void	ft_print(t_ls *ls);

#endif
