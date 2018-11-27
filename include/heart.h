/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heart.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 01:40:43 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 03:01:58 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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
# include <time.h>

# include <stdio.h>
# include <curses.h>
# include <fcntl.h>
# include <dirent.h>
# include <pwd.h>
# include <limits.h>

# include "../libft/include/libft.h"
# include "init.h"
# include "ft_select.h"
# include "line_edition.h"
# include "lexer.h"
# include "parsing.h"
# include "extension.h"
# include "builtins.h"
# include "execute.h"

char			**g_set;
int				g_interupt;
char			**g_env;
char			*g_cmd;
int				g_cursor_pos;
t_prompt		g_prompt;

int				heart_of_101sh(char *line, int fd_base);
void			signal_shell(void);
void			exit_shell(void);

void			ft_handle_resize(int sig);
void			ft_handle_sigint(int sig);

#endif
