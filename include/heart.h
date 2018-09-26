#ifndef HEART_H
# define HEART_H

# define BUFF_SIZE 4096
# define BI_MAX 4084
# define MAX_HASH 100

# include <unistd.h>
# include <signal.h>

# include <term.h>
# include <termios.h>

# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/utsname.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include <stdio.h>
# include <curses.h>
# include <fcntl.h>
# include <dirent.h>
# include <pwd.h>
# include <limits.h>

# include "../libft/include/libft.h"
# include "init.h"
# include "editor.h"
# include "ft_select.h"
# include "lexer.h"
# include "parsing.h"
# include "extension.h"
# include "builtins.h"
# include "execute.h"

char	**g_set;
char	**g_env;

int		heart_of_101sh(char *line, int fd_base);
void	signal_shell(void);
void	exit_shell(const char *bin);

#endif
