/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 08:23:31 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "heart.h"

# define BOLD "\x1b[1m"
# define UNDER "\x1b[4m"
# define REV "\x1b[7m"

# define IGREY "\x1b[40m"
# define IRED "\x1b[41m"
# define IGREEN "\x1b[42m"
# define IYELLOW "\x1b[43m"
# define IBLUE "\x1b[44m"
# define IPURPLE "\x1b[45m"
# define ICYAN "\x1b[46m"
# define IWHITE "\x1b[47m"

typedef struct termios	t_term;
typedef struct winsize	t_ws;

typedef struct			s_line
{
	char				*elem;
	int					x_char_pos;
	int					x_param_pos;
	int					y_pos;
	int					is_file;
	int					ds;
	int					cursor_inside;
//	int					select;
	struct s_line		*prev;
	struct s_line		*next;
}						t_line;

typedef struct			s_select
{
	t_ws				ws;
	char				*ret;
	int					pose_min;
	int					bp;
	int					pbl;
	int					nbl;
	int					nbp;
	char				*ds;
	t_line				*line;
}						t_select;

int						ft_select(t_editor **ed, char **line, int version);
void					ft_error(const char *s, t_select **t);
t_term					ft_save_raw_off(t_select **t);
char					*ft_read_entry(t_select **t);
void					ft_print_params(t_select *sel);
void					ft_get_size_term(t_ws *ws, t_select **t, int fd);
int						ft_manage_touch(t_editor **ed);
int						ft_arrows(char arrows, t_select **t, int *place);
int						ft_outc(int c);
void					ft_init_select(t_select **sel, char **av, int index, t_editor **ed);
int						ft_count_line(t_select *t);
int						ft_search_big_param(t_line *line);
int						ft_is_file(char *file);
void					ft_first_sort(t_line **line, char *av, int inside);
int						ft_count_params(t_line *line);
int						ft_char_by_line(t_select **sel);
t_line					*ft_prepare_print(int i[2], t_line *line, int nb_line);
int						ft_params_by_line(t_select *t);
int						ft_select_sp(t_select **t);
void					ft_print_select(t_line *str, int j, int bp, int v);
void					ft_decremente_select(int select, t_select **t);
void					ft_place_cursor(int nb_ret, int len_line, int v);
int						ft_free_t_select(t_select **t);
void					ft_save_shell(t_select **t, int version);
int						tabulator(t_editor **ed, int version);
int						ft_isdir(char *test);
char					*ft_search_pwd(char *ext);
int						ft_isechap(char c);
int						ft_isseparator(char c);
char					**ft_tabsplit(const char *s, int cursor_pos);

#endif
