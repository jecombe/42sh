/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backspace.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:10:17 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 18:12:09 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		backspace_next(t_editor *ed)
{
	char	tmp[ft_strlen(ed->line)];
	char	*cursor_reset;

	ft_strncpy(tmp, ed->line, ed->cursor_str_pos);
	ft_strcat(tmp, ed->line + (ed->cursor_str_pos + 1));
	ft_strdel(&(ed->line));
	if (ft_strlen(tmp))
		ed->line = ft_strdup(tmp);
	cursor_reset = cursor_position_escape_sequence(0, 0, ed);
	ft_putstr("\E[0J");
	ft_putstr(ed->line + ed->cursor_str_pos);
	reset_cursor_position_escape_sequence(&cursor_reset);
	ed->last_char--;
	if (ed->last_char == 0)
	{
		ed->last_char = ed->ws_col;
		ed->last_row--;
	}
}

int				backspace(t_editor *ed)
{
	ed->cursor_str_pos--;
	if (ed->line[ed->cursor_str_pos] == '\n')
	{
		move_to_previous_new_line(ed);
		ed->last_row--;
	}
	else if (ed->cur_col == 1)
	{
		ed->cur_col = ed->ws_col;
		tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, ed->ws_col - 1), 1, ft_putchar);
		ed->cur_row--;
	}
	else
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		ed->cur_col--;
	}
	return (0);
}
