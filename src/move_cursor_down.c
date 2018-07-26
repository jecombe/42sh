/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_down.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:52:03 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 20:46:26 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	move_cursor_down(char *line, t_editor *ed)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(1) != ed->last_row)
	{
		if (get_cursor_position(1) + 1 == ed->last_row && (ft_strlen(line
		+ ed->cursor_str_pos) - (sz.ws_col - get_cursor_position(0))
		< get_cursor_position(0)))
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, (ft_strlen(line +
			ed->cursor_str_pos) - (sz.ws_col - get_cursor_position(0))) - 1), 1,
			ft_putchar);
			ed->cursor_str_pos = ft_strlen(line);
		}
		else
			ed->cursor_str_pos = ed->cursor_str_pos + ((get_cursor_position(0) +
			(sz.ws_col - get_cursor_position(0))));
			tputs(tgoto(tgetstr("cv", NULL), 0, get_cursor_position(1)), 1,
			ft_putchar);
	}
}
