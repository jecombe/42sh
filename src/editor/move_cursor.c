/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:48:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 22:42:59 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	move_cursor_up(t_editor *ed)
{
	if (get_cursor_position(1) != ed->first_row)
	{
		if (get_cursor_position(1) - 1 == ed->first_row &&
		ed->cur_col < ed->first_char)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, ed->first_char - 1), 1,
			ft_putchar);
			ed->cursor_str_pos = 0;
		}
		else
			ed->cursor_str_pos = ed->cursor_str_pos - (get_cursor_position(0) +
			(ed->ws_col - get_cursor_position(0)));
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	}
}

void	move_cursor_down(t_editor *ed)
{
	if (ed->cur_row != ed->last_row)
	{
		if (ed->cur_row + 1 == ed->last_row && (ft_strlen(ed->line
		+ ed->cursor_str_pos) - (ed->ws_col - ed->cur_col)
		< ed->cur_col))
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, (ft_strlen(ed->line +
			ed->cursor_str_pos) - (ed->ws_col - ed->cur_col)) - 1), 1, ft_putchar);
			ed->cursor_str_pos = ft_strlen(ed->line);
		}
		else
			ed->cursor_str_pos = ed->cursor_str_pos + ((get_cursor_position(0) +
			(ed->ws_col - get_cursor_position(0))));
		tputs(tgoto(tgetstr("cv", NULL), 0, get_cursor_position(1)), 1,
		ft_putchar);
	}
}

void	move_cursor_left(t_editor *ed)
{
	if (ed->cursor_str_pos > 0)
	{
		ed->cursor_str_pos--;
		move_left(ed);
		ed->cur_col = get_cursor_position(0);
		ed->cur_row = get_cursor_position(1);
	}
}

void	move_cursor_right(t_editor *ed)
{
	if (ed->cursor_str_pos < ft_strlen(ed->line))
	{
		if (ed->line[ed->cursor_str_pos] == '\n')
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		else
			move_right();
		ed->cur_col = get_cursor_position(0);
		ed->cur_row = get_cursor_position(1);
		ed->cursor_str_pos++;
	}
}
