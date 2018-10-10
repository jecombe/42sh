/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backspace.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:10:17 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 21:09:37 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			backspace(t_editor *ed)
{
	char	tmp[ft_strlen(ed->line)];
	char	*cursor_reset;
	t_sz	sz;

	ioctl(0, TIOCGWINSZ, &sz);
	bzero(tmp, sizeof(tmp));
	ed->cursor_str_pos--;
	if (ed->line[ed->cursor_str_pos] == '\n')
	{
		move_to_previous_new_line(ed);
		ed->last_row--;
	}
	else if (ed->cur_col == 1)
	{
		ed->cur_col = sz.ws_col;
		tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
		ed->cur_row--;
	}
	else
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		ed->cur_col--;
	}
	ft_strncpy(tmp, ed->line, ed->cursor_str_pos);
	ft_strcat(tmp, ed->line + (ed->cursor_str_pos + 1));
	ft_strdel(&(ed->line));
	if (ft_strlen(tmp))
		ed->line = ft_strdup(tmp);
	cursor_reset = cursor_position_escape_sequence(0, 0, ed);
	ft_putstr("\E[0J");
	ft_putstr(ed->line + ed->cursor_str_pos);
		dprintf(2, "get_cursor_position(0): %zu\n", get_cursor_position(0));
	reset_cursor_position_escape_sequence(&cursor_reset);
		ed->last_char--;
		dprintf(2, "ed->last: %zu\n", ed->last_char);
	if (ed->last_char == 0)
	{
		dprintf(2, "ed->last_row: %zu\n", ed->last_row);
		ed->last_char = sz.ws_col;
		ed->last_row--;
		dprintf(2, "ed->last: %zu\n", ed->last_char);
	}
	return (0);
}
