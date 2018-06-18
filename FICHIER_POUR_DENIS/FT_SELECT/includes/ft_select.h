/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 01:20:54 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include <dirent.h>
# include <sys/ioctl.h>
# include <term.h>
# include "../libft/libft.h"

# define END "\x1b[0m"
# define BOLD "\x1b[1m"
# define UNDER "\x1b[4m"
# define REV "\x1b[7m"

# define GREY "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define PURPLE "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

# define IGREY "\x1b[40m"
# define IRED "\x1b[41m"
# define IGREEN "\x1b[42m"
# define IYELLOW "\x1b[43m"
# define IBLUE "\x1b[44m"
# define IPURPLE "\x1b[45m"
# define ICYAN "\x1b[46m"
# define IWHITE "\x1b[47m"

int		g_sign;

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
	float				select;
	struct s_line		*prev;
	struct s_line		*next;
}						t_line;

typedef struct			s_select
{
	t_ws				ws;
	int					select_max;
	int					pose_min;
	int					bp;
	int					pbl;
	int					nbl;
	int					nbp;
	char				*ds;
	t_line				*line;
}						t_select;

void					ft_error(const char *s, t_select **t);
t_term					ft_save_raw_off(t_select **t);
int						ft_disable_raw(int ret, t_select **t);
void					ft_enable_raw(t_select **t);
int						ft_manage_entry(char **ret, t_select **sel);
char					*ft_read_entry(t_select **t);
void					ft_print_params(t_select **sel);
void					ft_get_size_term(t_ws *ws, t_select **t, int fd);
int						ft_manage_touch(char **ret, t_select **t);
int						ft_arrows(char arrows, t_select **t);
int						ft_outc(int c);
void					ft_init_select(t_select **sel, char **av);
int						ft_count_line(t_select *t);
int						ft_search_big_param(t_line *line);
int						ft_is_file(char *file);
int						ft_del_maillon(t_select **t);
void					ft_first_sort(t_line **line, char *av);
int						ft_count_params(t_line *line);
int						ft_char_by_line(t_select **sel);
t_line					*ft_prepare_print(int i[2], t_line **line, int nb_line);
int						ft_params_by_line(t_select *t);
int						ft_select_sp(t_select **t);
void					ft_print_select(t_line *str, int j, int bp, int v);
void					ft_decremente_select(int select, t_select **t);
void					ft_place_cursor(int nb_ret, int len_line, int v);
int						ft_free_t_select(t_select **t);
void					ft_signal(void);
void					ft_save_shell(t_select **t, int version);
int						ft_test(t_select **sel, int ret);
int						ft_searchdyn(t_select **t, char ret);
void					ft_unhighlightds(t_select **t);

#endif
