/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_left.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:20:06 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 20:04:35 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void    move_to_next_new_line(t_editor *ed)
{
	int i;
	int tmp_cursor_str_pos;

	i = -1;
	tmp_cursor_str_pos = ed->cursor_str_pos - 1;
	tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
	while (ed->line[tmp_cursor_str_pos] != '\n')
		tmp_cursor_str_pos--;
	tmp_cursor_str_pos = ed->cursor_str_pos - (tmp_cursor_str_pos + 1);
	while (++i < tmp_cursor_str_pos)
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
}

void	move_left(t_editor *ed)
{
	t_sz sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(0) == 1 && ed->cursor_str_pos)
	{
		tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
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
