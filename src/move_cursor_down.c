/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_down.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:52:03 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/10 02:14:40 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	move_cursor_down(t_editor *ed)
{
	if (get_cursor_position(1) != ed->last_row)
	{
		ioctl(0, TIOCGWINSZ, &sz);
		if (get_cursor_position(1) + 1 == ed->last_row && (ft_strlen(ed->line
		+ ed->cursor_str_pos) - (sz.ws_col - get_cursor_position(0))
		< get_cursor_position(0)))
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, (ft_strlen(ed->line +
			ed->cursor_str_pos) - (sz.ws_col - get_cursor_position(0))) - 1), 1,
			ft_putchar);
			ed->cursor_str_pos = ft_strlen(ed->line);
		}
		else
			ed->cursor_str_pos = ed->cursor_str_pos + ((get_cursor_position(0) +
			(sz.ws_col - get_cursor_position(0))));
		tputs(tgoto(tgetstr("cv", NULL), 0, get_cursor_position(1)), 1,
		ft_putchar);
	}
}
