/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_left.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:20:06 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 23:27:46 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

void	move_cursor_left(t_editor *ed)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (ed->cursor_str_pos > 0)
	{
		ed->cursor_str_pos--;
		if (get_cursor_position(0) == 1 && ed->cursor_str_pos)
		{
			tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putchar);
	}
}
