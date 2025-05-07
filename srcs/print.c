
#include "../incl/ft_ls.h"

static void	ft_print_error(int err, char *name)
{
	if (err == E_ERR_EXIST)
		ft_printf("%s%s%s\n",D_ERR_MSG_EXIS_1, name, D_ERR_MSG_EXIS_2);
	else if (err == E_ERR_ACCESS)
		ft_printf("%s%s%s\n", D_ERR_MSG_PERM_1, name, D_ERR_MSG_PERM_2);
}

static void	ft_print_permissions(mode_t mode)
{
	char c;

	c = S_ISDIR(mode) ? 'd' :
	    S_ISLNK(mode) ? 'l' :
	    S_ISCHR(mode) ? 'c' :
	    S_ISBLK(mode) ? 'b' :
	    S_ISFIFO(mode) ? 'p' :
	    S_ISSOCK(mode) ? 's' : '-';
	ft_putchar(c);
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void	ft_print_extanded(t_long *extand, char *name)
{
	struct passwd	*pw = getpwuid(extand->uid);
	struct group	*gr = getgrgid(extand->gid);
	char			*time_str = ctime(&extand->time);

	ft_print_permissions(extand->mode);
	ft_printf(" %d ", extand->nlink);
	ft_printf("%s ", pw ? pw->pw_name : "unknown");
	ft_printf("%s ", gr ? gr->gr_name : "unknown");
	ft_printf("%D ", (size_t)extand->size);
	if (time_str)
	{
		time_str[16] = '\0';
		ft_printf("%s ", time_str + 4);
	}
	ft_printf("%s", name);
	if (S_ISLNK(extand->mode))
	{
		char buf[1024];
		ssize_t len = readlink(name, buf, sizeof(buf) - 1);
		if (len != -1)
		{
			buf[len] = '\0';
			ft_printf(" -> %s", buf);
		}
	}
}

static void	ft_print_block(t_file *ptr)
{
	struct stat st;
	int total_blocks = 0;
	while (ptr)
	{
		if (lstat(ptr->path, &st) == 0)
			total_blocks += st.st_blocks;
		else
			ft_error(ptr->path, 1);
		ptr = ptr->next;
	}
	ft_printf("total %d\n", total_blocks / 2);
}

static void	ft_print_path_name(t_path *path, bool multiple, bool extand)
{
	if (path->error)
	{
		ft_print_error(path->error, path->name);
		return ;
	}
	if (path->folder != true)
	{
		if (extand)
			ft_print_extanded(path->extand, path->name);
		else
			ft_printf("%s", path->name);
	}
	if (path->folder == true && multiple == true)
		ft_printf("%s:\n", path->name);
	if (!path->folder && path->next != NULL && path->next->folder != true)
		ft_printf("  ");
	else if (!path->folder && path->next)
		ft_printf("\n\n");
}

static void	ft_print_file(t_file *ptr, bool extand)
{
	if (extand)
		ft_print_block(ptr);
	while (ptr != NULL)
	{
		if (extand)
		{
			ft_print_extanded(ptr->extand, ptr->name);
			if (ptr->next != NULL)
				ft_printf("\n");
		}
		else
		{
			ft_printf("%s", ptr->name);
			if (ptr->next != NULL)
				ft_printf("  ");
		}
		ptr = ptr->next;
	}
	ft_printf("\n");
}

/* Print the output in the good format if recursive */
static void	ft_print_recursive(t_path *path, t_option option)
{
	ft_print_path_name(path, true, option.long_listing);
	ft_print_file(path->file, option.long_listing);
	ft_printf("\n");
	t_file	*ptr = path->file;
	while (ptr != NULL)
	{
		if (ptr->type == E_FOLDER)
		{
			char	*path_name = ft_str_join_path(path->name, ptr->name);
			t_path	*rec = ft_lst_path_new(path_name, option);
			rec->file = ft_swap(rec->file, option, true);
			ft_print_recursive(rec, option);
			free(path_name);
			free(rec);
		}
		ptr = ptr->next;
	}
}

void	ft_print(t_ls *ls)
{
	t_path	*path = ls->path;
	t_option option;
	option.hidden = ft_is_option(E_OPTION_A, ls->option);
	option.time = ft_is_option(E_OPTION_T, ls->option);
	option.long_listing = ft_is_option(E_OPTION_L, ls->option);
	option.reverse = ft_is_option(E_OPTION_R, ls->option);
	while (path != NULL)
	{
		if (ls->rec)
			ft_print_recursive(path, option);
		else
		{
			ft_print_path_name(path, ls->multiple, option.long_listing);
			if (path->folder && !path->error)
			{
				ft_print_file(path->file, option.long_listing);
				if (path->next)
					ft_printf("\n");
			}
		}
		path = path->next;
	}
}

/* Print help message on how to use 'ls' */
void	ft_print_help(void)
{
	ft_printf("Usage: ft_ls [OPTION]... [FILE]...\n"\
			"List information about the FILEs (the current directory by default).\n"\
			"Sort entries alphabetically if -tr is specified.\n\n"\
			"Mandatory arguments to long options are mandatory for short options too.\n"\
			"-a, --all                  do not ignore entries starting with .\n"\
			"-l                         use a long listing format\n"\
			"-r, --reverse              reverse order while sorting \n"\
			"-R, --recursive            list subdirectories recursively\n"\
			"-t                         sort by time, newest first; see --time\n"\
			"The SIZE argument is an integer and optional unit (example: 10K is 10*1024).\n"\
			"Units are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).\n"\
			"Binary prefixes can be used, too: KiB=K, MiB=M, and so on.\n\n"\
			"The TIME_STYLE argument can be full-iso, long-iso, iso, locale, or +FORMAT.\n"\
			"FORMAT is interpreted like in date(1).  If FORMAT is FORMAT1<newline>FORMAT2,\n"\
			"Also the TIME_STYLE environment variable sets the default style to use.\n\n"\
			"Exit status:\n"\
			" 0  if OK,\n"\
			" 1  if minor problems (e.g., cannot access subdirectory),\n"\
			" 2  if serious trouble (e.g., cannot access command-line argument).\n"\
			"Full documentation <https://github.com/MrMobbi/ft_ls>\n");
}
