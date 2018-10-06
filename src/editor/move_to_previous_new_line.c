/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_to_next_new_line.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 19:39:48 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 19:40:04 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void    move_to_previous_new_line(t_editor *ed)
{
	int i;
	int tmp_cursor_str_pos;

	i = -1;
	tmp_cursor_str_pos = ed->cursor_str_pos - 1;
	if (get_cursor_position(1) - 1 == ed->first_row)
	{
		tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 1, (ed->prompt_size - 1) +
		ed->cursor_str_pos), 1, ft_putchar);
	}
	else
	{
		tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
		while (ed->line[tmp_cursor_str_pos] != '\n')
			tmp_cursor_str_pos--;
		tmp_cursor_str_pos = ed->cursor_str_pos - (tmp_cursor_str_pos + 1);
		while (++i < tmp_cursor_str_pos)
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
}
