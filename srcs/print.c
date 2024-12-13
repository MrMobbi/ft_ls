
#include "../incl/ft_ls.h"

void	ft_print_multiple(t_ls ls)
{
	t_path	*path = ls.path;
	printf("\n");
}

void	ft_print_folder(t_path *path)
{
	t_file	*file = path->file;

	while (file != NULL)
	{
		if (file->type < 10)
			printf(file->name);
		if (file->next != NULL)
			printf(" ");
		file = file->next;
	}
	printf("\n");
}

void	ft_print_single(t_ls ls)
{
	printf("PRINTING SINGLE\n");
	t_path	*path = ls.path;
	if (path->folder == true)
		ft_print_folder(path);
	else
	{
		while (path != NULL)
		{
			printf("%s", path->name);
			if (path->next != NULL)
				printf(" ");
			path = path->next;
		}
		printf("\n");
	}
}

void	ft_print(t_ls ls)
{
	t_path	*path = ls.path;
	int		different = 0;
	while (path != NULL)
	{
		if (path->folder == true)
			different++;
		if (different == 0)
			different++;
		path = path->next;
	}
	if (different > 1)
		ft_print_multiple(ls);
	else
		ft_print_single(ls);
}

void	ft_print_help(void)
{
	printf("Usage: ls [OPTION]... [FILE]...\n"\
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
			"then FORMAT1 applies to non-recent files and FORMAT2 to recent files.\n"\
			"TIME_STYLE prefixed with 'posix-' takes effect only outside the POSIX locale.\n"\
			"Also the TIME_STYLE environment variable sets the default style to use.\n\n"\
			"The WHEN argument defaults to 'always' and can also be 'auto' or 'never'.\n\n"\
			"Using color to distinguish file types is disabled both by default and\n"\
			"with --color=never.  With --color=auto, ls emits color codes only when\n"\
			"standard output is connected to a terminal.  The LS_COLORS environment\n"\
			"variable can change the settings.  Use the dircolors(1) command to set it.\n\n"\
			"Exit status:\n"\
			" 0  if OK,\n"\
			" 1  if minor problems (e.g., cannot access subdirectory),\n"\
			" 2  if serious trouble (e.g., cannot access command-line argument).\n"\
			"Full documentation <https://github.com/MrMobbi/ft_ls>\n");
	exit(0);
}
