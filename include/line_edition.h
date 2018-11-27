/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_edition.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/26 08:10:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 12:30:29 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "heart.h"

# define FT_KEY_CTRL_C		(char[4]){   3,   0,   0,   0 }
# define FT_KEY_CTRL_D		(char[4]){   4,   0,   0,   0 }
# define FT_KEY_CTRL_L		(char[4]){  12,   0,   0,   0 }
# define FT_KEY_TAB			(char[4]){   9,   0,   0,   0 }
# define FT_KEY_ENTER		(char[4]){  10,   0,   0,   0 }
# define FT_KEY_BCKSPACE	(char[4]){ 127,   0,   0,   0 }
# define FT_KEY_DEL			(char[4]){  27,  91,  51, 126 }
# define FT_KEY_HOME		(char[4]){  27,  91,  72,   0 }
# define FT_KEY_END			(char[4]){  27,  91,  70,   0 }
# define FT_KEY_UP			(char[4]){  27,  91,  65,   0 }
# define FT_KEY_DOWN		(char[4]){  27,  91,  66,   0 }
# define FT_KEY_LEFT		(char[4]){  27,  91,  68,   0 }
# define FT_KEY_RIGHT		(char[4]){  27,  91,  67,   0 }

# define FT_KEY_ALT_UP		(char[4]){  27,  27,  91,  65 }
# define FT_KEY_ALT_DOWN	(char[4]){  27,  27,  91,  66 }
# define FT_KEY_ALT_LEFT	(char[4]){  27,  27,  91,  68 }
# define FT_KEY_ALT_RIGHT	(char[4]){  27,  27,  91,  67 }

# define FT_KEY_UPDOWN		(char[4]){  27,  91, -101,    0 }
# define FT_KEY_LEFTRIGHT	(char[4]){  27,  91, -102,    0 }
# define FT_KEY_HOME_END	(char[4]){  27,  91, -103,    0 }
# define FT_KEY_ALT_UD		(char[4]){  27,  27,   91, -101 }
# define FT_KEY_ALT_LR		(char[4]){  27,  27,   91, -102 }

# define TERMCAP(x) tputs(tgetstr(x, NULL), 1, ft_putchar)
# define TERMCAPGO(x, y) tputs(tgoto(tgetstr(x, NULL), 0, y), 1, ft_putchar)
# define WHITE "\033[7;49;37"
# define END "\033[0m"

typedef struct termios		t_termios;
typedef struct s_select		t_select;
typedef struct winsize		t_ws;
struct s_shell;

typedef struct	s_key
{
	char		key[4];
	int			(*f)(struct s_shell *sh, char key[3]);
}				t_key;

typedef enum	e_prompt
{
	PROMPT,
	B_QUOTE,
	S_QUOTE,
	D_QUOTE,
	DB_QUOTE,
	E_HDOC,
	E_PIPE,
	BACKSLASH,
	ORIF,
	ANDIF,
	SUBST,
	READ
}				t_prompt;

typedef struct	s_tab
{
	char		**cmd;
	char		**elem;
	char		*is_file;
	char		*before;
	char		*word;
	int			nb_word;
	int			nb_char;
	int			nb_line;
}				t_tab;

typedef struct	s_shell
{
	t_ws		ws;
	int			prompt_len;
	t_key		keys[100];
	char		*tmp_line;
	t_tab		t;
	t_select	*sel;
	int			hist;
	int			tabu;
}				t_shell;

int				ft_get_git_branch(char buff[]);
int				display_prompt(t_prompt prompt);
void			ft_miniconcat(char **s1, char *s2);
void			ft_print_git_branch(void);
void			ft_putfreshstr(char *str);
void			gm_goto(int nb, void (*f) (int, int), int len, int col);
char			**ft_cmd_split(t_shell *ed);
void			ft_pushed_left(t_shell *sh);
void			ft_pushed_right(t_shell *sh);
void			init_tab_and_hist(t_shell *sh, char key[5]);
void			init_hist(t_shell *sh, char key[5]);
void			init_tab(t_shell *sh, char key[5]);
void			ft_insert_to_line(t_shell *sh, char *buff);
void			ft_putcmd(t_shell *sh, int new_pos);
int				ft_recup_cursor_pos(t_shell *sh, int *left_xpos,
		int *right_xpos);
int				ft_count_line_cmd(t_shell *sh);
int				ft_reprint_cmd(t_shell *sh);
char			*ft_get_user_input(t_prompt *prompt);
int				ft_input_check(char key[], char buff[]);
void			ft_init_input_keys(t_shell *sh);
void			ft_left_move(int len, int col);
void			ft_right_move(int len, int col);
int				ft_pushed_key_home_end(t_shell *sh, char key[]);
int				ft_pushed_key_altup_altdown(t_shell *sh, char key[]);
int				ft_pushed_key_altleft_altright(t_shell *sh, char key[]);
int				ft_pushed_key_backspace(t_shell *sh, char key[]);
int				ft_pushed_key_del(t_shell *sh, char key[]);
int				ft_pushed_key_enter(t_shell *sh, char key[]);
int				ft_pushed_left_right(t_shell *sh, char key[]);
int				ft_pushed_up_down(t_shell *sh, char key[]);
int				ft_pushed_key_tab(t_shell *sh, char key[]);
int				ft_pushed_key_ctrl_c(t_shell *sh, char key[]);
int				ft_pushed_key_ctrl_d(t_shell *sh, char key[]);
int				ft_pushed_key_ctrl_l(t_shell *sh, char key[]);
int				ft_init_shell_struct(t_shell *sh, t_prompt *prompt);
int				get_term_raw_mode(int mode);
void			ft_read_raw_mode();
void			ft_get_cols(t_ws *ws);

#endif
