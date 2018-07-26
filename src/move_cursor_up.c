/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_up.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:48:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 20:36:11 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	move_cursor_up(t_editor *ed)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(1) != ed->first_row)
	{
		if (get_cursor_position(1) - 1 == ed->first_row &&
		get_cursor_position(0) < ed->prompt_size)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, ed->prompt_size - 1), 1,
			ft_putchar);
			ed->cursor_str_pos = 0;
		}
		else
			ed->cursor_str_pos = ed->cursor_str_pos - (get_cursor_position(0) +
			(sz.ws_col - get_cursor_position(0)));
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	}
}
