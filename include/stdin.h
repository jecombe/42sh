/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stdin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 08:51:01 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 03:53:53 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STDIN_H
# define STDIN_H

# define BLUE "\033[1;49;36m"
# define WHITE "\033[7;49;37m"
# define RED "\033[7;49;91m"
# define END "\033[0m"
# define LEFT_KEY (ed->key[0] == 27 && ed->key[1] == 91 && ed->key[2] == 68)
# define RIGHT_KEY (ed->key[0] == 27 && ed->key[1] == 91 && ed->key[2] == 67)
# define UP_KEY (ed->key[0] == 27 && ed->key[1] == 91 && ed->key[2] == 65)
# define DOWN_KEY (ed->key[0] == 27 && ed->key[1] == 91 && ed->key[2] == 66)
# define SPACE_KEY (ed->key[0] == 32 && ed->key[1] == 0)
# define TAB_KEY (ed->key[0] == 9 && ed->key[1] == 0)
# define BS_KEY (ed->key[0] == 127 && ed->key[1] == 0)
# define ENTER_KEY (ed->key[0] == 10 && ed->key[1] == 0)
# define BACKSPACE (ed->key[0] == 127 && ed->key[1] == 0)
# define CTRL_C (ed->key[0] == 3 && ed->key[1] == 0)
# define CTRL_D (ed->key[0] == 4 && ed->key[1] == 0)
# define CTRL_L (ed->key[0] == 12 && ed->key[1] == 0)
# define CTRL_K (ed->key[0] == 11 && ed->key[1] == 0)
# define CTRL_U (ed->key[0] == 21 && ed->key[1] == 0)
# define CTRL_W (ed->key[0] == 23 && ed->key[1] == 0)
# define CTRL_P (ed->key[0] == 16 && ed->key[1] == 0)
# define HOME_KEY (ed->key[0] == 27 && ed->key[1] == 91 && ed->key[2] == 72)
# define END_KEY (ed->key[0] == 27 && ed->key[1] == 91 && ed->key[2] == 70)
# define SHIFT_UP "\E[1;2A"
# define SHIFT_DOWN "\E[1;2B"
# define SHIFT_LEFT "\E[1;2D"
# define SHIFT_RIGHT "\E[1;2C"
# include "../libft/include/libft.h"
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>

char			**g_env;
struct winsize sz;

typedef enum		s_prompt
{
	PROMPT,
	B_QUOTE,
	S_QUOTE,
	D_QUOTE,
	E_HDOC,
	E_PIPE,
}					e_prompt;

typedef struct		s_editor
{
	size_t	first_row;
	size_t	last_row;
	size_t	prompt_size;
	size_t	cursor_str_pos;
	char	*clipboard;
	char	key[10];
}					t_editor;

int		g_bin_exit;
//char	*g_save_home;

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

int		clear_window(char *line, t_editor *ed, e_prompt prompt);
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
void	display_prompt(char *home, e_prompt prompt);
int		get_stdin(char **line, e_prompt prompt);
char	*find_var_string(char **env, char *var, int mode);
void	myhandler_winsize_change(int signal);
size_t	get_cursor_position(int mode);
void	delete_from_cursor_to_end(char **line, t_editor *ed);
void	paste_clipboard(char **line, t_editor *ed);

#endif
