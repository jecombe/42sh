/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/11 21:47:43 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/17 20:49:30 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# define BLUE "\033[1;49;36m"
# define WHITE "\033[7;49;37m"
# define RED "\033[7;49;91m"
# define END "\033[0m"
# define LEFT_KEY (key[0] == 27 && key[1] == 91 && key[2] == 67 && key[3] == 0)
# define RIGHT_KEY (key[0] == 27 && key[1] == 91 && key[2] == 68 && key[3] == 0)
# define UP_KEY (key[0] == 27 && key[1] == 91 && key[2] == 65)
# define DOWN_KEY (key[0] == 27 && key[1] == 91 && key[2] == 66)
# define SPACE_KEY (key[0] == 32 && key[1] == 0)
# define TAB_KEY (key[0] == 9 && key[1] == 0)
# define BS_KEY (key[0] == 127 && key[1] == 0)
# define ENTER_KEY (key[0] == 10 && key[1] == 0)
# define BACKSPACE (key[0] == 127 && key[1] == 0)
# define CTRLD (key[0] == 4 && key[1] == 0)
# define CTRLL (key[0] == 12 && key[1] == 0)
# define HOME_KEY (key[0] == 27 && key[1] == 91 && key[2] == 72 && key[3] == 0)
# define END_KEY (key[0] == 27 && key[1] == 91 && key[2] == 70 && key[3] == 0)
# define SHIFT_UP "\E[1;2A"
# define SHIFT_DOWN "\E[1;2B"
# define SHIFT_LEFT "\E[1;2D"
# define SHIFT_RIGHT "\E[1;2C"
# include "../libft/includes/libft.h"
# include "stdin.h"
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

struct winsize sz;

typedef struct		s_shell
{
	int				err;
	char			*line;
	char			**my_env;
	char			**bin_path;
	char			pwd[4096];
	char			last_path[4096];
	char			save_home[4096];
}					t_shell;

size_t	g_cursor_row_number;
size_t	g_row_number;
size_t	g_prompt_size;
size_t	g_cursor_col_pos;
size_t	g_cursor_str_pos;
size_t	g_home_position;
int		g_bin_exit;
char	*g_save_line;
char	*g_save_home;
void	myhandler_interrupt(int signal);
char	*cut_pwd_dir(char *pwd);
void	display_prompt(char *pwd, char *home, int err, char *rwd);
int		get_stdin(t_shell *sh, char **line);
char	*find_var_string(char **env, char *var, int mode);
void	myhandler_winsize_change(int signal);
int		clear_window(t_shell *sh);
int		get_cursor_position(int mode);

#endif
