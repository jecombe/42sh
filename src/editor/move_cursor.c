/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:48:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 23:56:56 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	move_cursor_up(t_editor *ed)
{
	t_sz sz;

	ft_memset(&sz, 0 , sizeof(sz));
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

void	move_cursor_down(t_editor *ed)
{
	t_sz sz;

	ft_memset(&sz, 0 , sizeof(sz));
	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(1) != ed->last_row)
	{
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

void		move_cursor_right(t_editor *ed)
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
