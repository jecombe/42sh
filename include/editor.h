/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   editor.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/10 00:46:23 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 02:43:15 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "heart.h"

# define WHITE "\033[7;49;37m"
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
# define CTRL_A (ed->key[0] == 1 && ed->key[1] == 0)
# define CTRL_E (ed->key[0] == 5 && ed->key[1] == 0)
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

typedef struct winsize	t_sz;
typedef struct dirent	t_dirent;

typedef enum		s_prompt
{
	PROMPT,
	B_QUOTE,
	S_QUOTE,
	D_QUOTE,
	DB_QUOTE,
	E_HDOC,
	E_PIPE,
	BACKSLASH,
}					e_prompt;

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_editor
{
	size_t	ws_row;
	size_t	ws_col;
	size_t	first_row;
	size_t	last_row;
	size_t	prompt_size;
	size_t	cursor_str_pos;
	char	*clipboard;
	char	key[BUFF_SIZE];
	char *line;
}					t_editor;

typedef struct		s_tab
{
	char	d_name[4096];
	struct s_tab	*next;
}					t_tab;

int		g_bin_exit;
//char	*g_save_home;

/*
*******************************************************************************
**                              CURSOR_MOVEMENT                               *
*******************************************************************************
*/

void	move_cursor_left(t_editor *ed);
void	move_cursor_right(t_editor *ed);
void	move_cursor_up(t_editor *ed);
void	move_cursor_down(t_editor *ed);
void	move_word_left(t_editor *ed);
void	move_word_right(t_editor *ed);
void	go_to_begin_of_line(t_editor *ed);
void	go_to_end_of_line(t_editor *ed);
int		backspace(t_editor *ed);

/*
*******************************************************************************
**                                     CTRL                                   *
*******************************************************************************
*/

int		clear_window(t_editor *ed, e_prompt prompt);
void	end_of_text(t_editor *ed, e_prompt *prompt, char **line);
void	myhandler_interrupt(int signal);

/*
** ****************************************************************************
**                              SAVE_RESET_CURSOR_POS                         *
** ****************************************************************************
*/

char	*cursor_position_escape_sequence(int row, int col);
void	reset_cursor_position_escape_sequence(char **cursor_position);

void	add_char_into_line(char key, t_editor *ed);
int		add_char_to_line(char key, t_editor *ed);
char	*cut_pwd_dir(char *pwd);
void	display_prompt(char *home, e_prompt prompt);
int		get_stdin(char **line, e_prompt *prompt);
void	myhandler_winsize_change(int signal);
size_t	get_cursor_position(int mode);
void	delete_from_cursor_to_end(t_editor *ed);
void	paste_clipboard(t_editor *ed);
int		get_term_raw_mode(int mode);
void	save_ed(t_editor **ed, int mode);
void	tabulator(t_editor *ed);
void	historic(t_editor *ed);
void	fill_hist_list(t_hist *hist, char *line);
int		term_reinit(struct termios *raw_mode);
int		get_term_raw_mode(int mode);
char	*find_env_var(char **env, char *var, int mode);

#endif
