/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 02:51:08 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 06:48:56 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		term_reinit(struct termios *raw_mode)
{
	static struct termios	term_default;
	static int				state = 0;

	if (state == 0)
	{
		tcgetattr(STDIN_FILENO, &term_default);
		state = 1;
	}
	*raw_mode = term_default;
	return (0);
}

int		get_term_raw_mode(int mode)
{
	struct termios raw_mode;

	term_reinit(&raw_mode);
	if (mode)
	{
		raw_mode.c_lflag &= ~(ECHO | ICANON | ISIG);
		raw_mode.c_cflag &= ~(CSIZE | PARENB);
		raw_mode.c_cflag |= CS8;
		raw_mode.c_cc[VMIN] = 0;
		raw_mode.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	return (0);
}

t_editor	*line_editor_init(char **line, e_prompt prompt)
{
	t_editor *ed;

	if (!(ed = (t_editor *)malloc(sizeof(t_editor))))
		return (NULL);
	ed->ret = 0;
	ed->cur_pos = get_cursor_position(0);
	ed->cursor_str_pos = 0;
	ed->ws_row = 0;
	ed->ws_col = 0;
	ed->first_row = get_cursor_position(1);
	ed->last_row = ed->first_row;
	ed->prompt_size = get_cursor_position(0);
	ed->line = NULL;
	ed->tmp_line = NULL;
	ed->clipboard = NULL;
	ft_bzero(ed->key, 4);
	ft_memset(&(ed)->t, 0, sizeof(t_tab));
	ed->sel = NULL;
	ed->hist = -2;
	ed->tabu = -1;
	if (prompt != PROMPT && prompt != E_PIPE)
		*line = ft_strjoin_free(*line, "\n");
	return (ed);
}

int				line_editor_delete(t_editor **ed)
{
	int		ret;

	ret = 0;
	ret = (*ed)->ret;
	ft_strdel(&(*ed)->line);
	ft_strdel(&(*ed)->tmp_line);
	ft_strdel(&(*ed)->clipboard);
	free(*ed);
	return (ret);
}
