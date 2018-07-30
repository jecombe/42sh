/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stdin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 08:51:01 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 02:15:29 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STDIN_H
# define STDIN_H
# define BUFF_SIZE 4096
# define BLUE "\033[1;49;36m"
# define WHITE "\033[7;49;37m"
# define RED "\033[7;49;91m"
# define END "\033[0m"
# define LEFT_KEY (key[0] == 27 && key[1] == 91 && key[2] == 68)
# define RIGHT_KEY (key[0] == 27 && key[1] == 91 && key[2] == 67)
# define UP_KEY (key[0] == 27 && key[1] == 91 && key[2] == 65)
# define DOWN_KEY (key[0] == 27 && key[1] == 91 && key[2] == 66)
# define SPACE_KEY (key[0] == 32 && key[1] == 0)
# define TAB_KEY (key[0] == 9 && key[1] == 0)
# define BS_KEY (key[0] == 127 && key[1] == 0)
# define ENTER_KEY (key[0] == 10 && key[1] == 0)
# define BACKSPACE (key[0] == 127 && key[1] == 0)
# define CTRL_C (key[0] == 3 && key[1] == 0)
# define CTRL_D (key[0] == 4 && key[1] == 0)
# define CTRL_L (key[0] == 12 && key[1] == 0)
# define CTRL_K (key[0] == 11 && key[1] == 0)
# define CTRL_U (key[0] == 21 && key[1] == 0)
# define CTRL_W (key[0] == 23 && key[1] == 0)
# define CTRL_P (key[0] == 16 && key[1] == 0)
# define HOME_KEY (key[0] == 27 && key[1] == 91 && key[2] == 72 && key[3] == 0)
# define END_KEY (key[0] == 27 && key[1] == 91 && key[2] == 70 && key[3] == 0)
# define SHIFT_UP "\E[1;2A"
# define SHIFT_DOWN "\E[1;2B"
# define SHIFT_LEFT "\E[1;2D"
# define SHIFT_RIGHT "\E[1;2C"
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>

struct winsize sz;

typedef enum		s_prompt
{
	PROMPT,
	B_QUOTE,
	S_QUOTE,
	D_QUOTE,
	HDOC,
	PIPE,
	CMDSUB,
	MATHSUB,
	BRACEPARA,

}					e_prompt;

typedef struct		s_editor
{
	size_t	first_row;
	size_t	last_row;
	size_t	prompt_size;
	size_t	cursor_str_pos;
	char	*clipboard;
}					t_editor;

typedef struct		s_shell
{
	int		err;
	char	*line;
	char	**bin_path;
	char	pwd[4096];
	char	last_path[4096];
	char	save_home[4096];
}					t_shell;

int		g_bin_exit;
char	*g_save_home;

/*
*******************************************************************************
**                              CURSOR_MOVEMENT                               *
*******************************************************************************
*/

void	move_cursor_left(t_editor *ed);
void	move_cursor_right(t_editor *ed, char *line);
void	move_cursor_up(t_editor *ed);
void	move_cursor_down(char *line, t_editor *ed);
void	move_word_left(char *line, t_editor *ed);
void	move_word_right(char *line, t_editor *ed);
void	go_to_begin_of_line(t_editor *ed);
void	go_to_end_of_line(t_editor *ed, char *line);
int		backspace(t_editor *ed, char **line);

/*
*******************************************************************************
**                                     CTRL                                   *
*******************************************************************************
*/

int		clear_window(t_shell *sh, t_editor *ed);
void	end_of_text(char **line, t_editor *ed);
void	myhandler_interrupt(int signal);

/*
** ****************************************************************************
**                              SAVE_RESET_CURSOR_POS                         *
** ****************************************************************************
*/

char	*cursor_position_escape_sequence(int row, int col);
void	reset_cursor_position_escape_sequence(char **cursor_position);

int		add_char_into_line(char key, char **line, t_editor *ed);
int		add_char_to_line(char key, t_editor *ed);
char	*cut_pwd_dir(char *pwd);
int		display_prompt(char *pwd, char *home, int err, char *rwd);
int		get_stdin(char **line, char **env, e_prompt prompt);
char	*find_var_string(char **env, char *var, int mode);
void	myhandler_winsize_change(int signal);
size_t	get_cursor_position(int mode);
void	delete_from_cursor_to_end(char **line, t_editor *ed);
void	paste_clipboard(char **line, t_editor *ed);

#endif
