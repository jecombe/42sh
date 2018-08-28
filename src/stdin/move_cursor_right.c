/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_right.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:30:23 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 23:27:46 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

void	move_cursor_right(t_editor *ed)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (ed->cursor_str_pos < ft_strlen(ed->line))
	{
		ed->cursor_str_pos++;
		if (get_cursor_position(0) == sz.ws_col)
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		else
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
}
