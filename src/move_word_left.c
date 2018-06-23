/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_word_left.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:54:46 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 08:45:12 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	move_word_left(t_shell *sh, t_editor *ed)
{
	size_t s_pos;
	char *cursor_reset;

	s_pos = ed->cursor_str_pos;
	cursor_reset = cursor_position_escape_sequence(0, 0);
	while (ed->cursor_str_pos)
	{
		if ((sh->line[ed->cursor_str_pos - 1] == ' ' || sh->line
		[ed->cursor_str_pos - 1] == '\t') && sh->line[ed->cursor_str_pos] >= 33
		&& sh->line[ed->cursor_str_pos] <= 126 && s_pos != ed->cursor_str_pos)
			return ;
		if (get_cursor_position(0) == 1)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putchar);
		ed->cursor_str_pos--;
	}
	if (sh->line[0] == '\t' || sh->line[0] == ' ')
	{
		ed->cursor_str_pos = s_pos;
		reset_cursor_position_escape_sequence(&cursor_reset);
	}
}
