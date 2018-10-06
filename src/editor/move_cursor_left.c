/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_left.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:20:06 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 19:45:24 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	move_left(t_editor *ed)
{
	t_sz sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(0) == 1 && ed->cursor_str_pos)
	{
		if (ed->line[ed->cursor_str_pos] == '\n')
			move_to_previous_new_line(ed);
		else
		{
			tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
		}
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
}

void	move_cursor_left(t_editor *ed)
{
	if (ed->cursor_str_pos > 0)
	{
		ed->cursor_str_pos--;
		move_left(ed);
	}
}
