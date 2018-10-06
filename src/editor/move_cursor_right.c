/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_right.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:30:23 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:07:21 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	move_right(void)
{
	t_sz sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(0) == sz.ws_col)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
}

void		move_cursor_right(t_editor *ed)
{
	if (ed->cursor_str_pos < ft_strlen(ed->line))
	{
		if (ed->line[ed->cursor_str_pos] == '\n')
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		else
			move_right();
		ed->cursor_str_pos++;
	}
}
