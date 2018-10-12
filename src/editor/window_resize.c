/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   window_resize.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 21:40:31 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 18:11:08 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	window_resize(t_editor **ed, e_prompt *prompt)
{
	t_sz	ws;
	size_t	cursor_str_pos_tmp;

	ft_memset(&ws, 0, sizeof(ws));
	cursor_str_pos_tmp = 0;
	cursor_str_pos_tmp = (*ed)->cursor_str_pos;
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	display_prompt(*prompt);
	(*ed)->first_char = get_cursor_position(0);
	(*ed)->first_row = get_cursor_position(1);
	ft_putstr((*ed)->line);
	(*ed)->last_row = get_cursor_position(1);
	(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
	while ((*ed)->cursor_str_pos != cursor_str_pos_tmp)
		move_cursor_left(*ed);
	if ((*ed)->tabu != -1)
	{
		ft_strdel(&(*ed)->tmp_line);
		tabulator(ed, 2);
	}
}

int			term_size(t_editor *ed)
{
	t_sz	sz;

	ft_memset(&sz, 0, sizeof(sz));
	if (ioctl(0, TIOCGWINSZ, &sz) == -1)
		return (EXIT_FAILURE);
	if (ed->ws_col == sz.ws_col && ed->ws_row == sz.ws_row)
		return (EXIT_FAILURE);
	ed->ws_col = sz.ws_col;
	ed->ws_row = sz.ws_row;
	return (EXIT_SUCCESS);
}
