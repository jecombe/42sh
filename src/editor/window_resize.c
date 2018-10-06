/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   window_resize.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 21:40:31 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 22:12:58 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	window_resize(t_editor **ed, t_sz ws, e_prompt *prompt)
{
	size_t cursor_str_pos_tmp;

	cursor_str_pos_tmp = (*ed)->cursor_str_pos;
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	display_prompt(*prompt);
	(*ed)->prompt_size = get_cursor_position(0);
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
	(*ed)->ws_col = ws.ws_col;
}
