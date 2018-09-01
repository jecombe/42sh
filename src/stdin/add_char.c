/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_char.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 10:42:22 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 23:25:54 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

int		add_char_into_line(char key, t_editor *ed)
{
	char tmp[ft_strlen(ed->line) + 2];
	char *cursor_reset;

	ed->cursor_str_pos++;
	ft_bzero(tmp, sizeof(tmp));
	ioctl(0, TIOCGWINSZ, &sz);
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	if ((!((ft_strlen(ed->line) + ed->prompt_size) % sz.ws_col) && ed->last_row == sz.ws_row))
	{
		if (!((get_cursor_position(0)) % sz.ws_col))
		{
			ft_putchar(key);
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
		else
			ft_putchar(key);
		cursor_reset = cursor_position_escape_sequence(1, 0);
		tputs(tgoto(tgetstr("DO", NULL), 0, (ed->last_row - get_cursor_position(1))), 1, ft_putchar);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		reset_cursor_position_escape_sequence(&cursor_reset);
		ed->first_row--;
	}
	else if (!((ft_strlen(ed->line) + ed->prompt_size) % sz.ws_col))
	{
		ft_putchar(key);
		if (!(get_cursor_position(0) % sz.ws_col))
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		ed->last_row++;
	}
	else if (!(get_cursor_position(0) % sz.ws_col))
	{
		ft_putchar(key);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	}
	else
		ft_putchar(key);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ft_strncpy(tmp, ed->line, ed->cursor_str_pos);
	tmp[ed->cursor_str_pos - 1] = key;
	ft_strcat(tmp, ed->line + ed->cursor_str_pos - 1);
	ft_strdel(&(ed->line));
	ed->line = ft_strdup(tmp);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, ed->line + ed->cursor_str_pos, ft_strlen(ed->line + ed->cursor_str_pos));
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	return (0);
}

int		add_char_to_line(char key, t_editor *ed)
{
	ioctl(0, TIOCGWINSZ, &sz);
	ed->cursor_str_pos++;
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	if (get_cursor_position(0)  == sz.ws_col &&
	get_cursor_position(1) != sz.ws_row)
	{
		ft_putchar(key);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		ed->last_row++;
	}
	else if (get_cursor_position(0) == sz.ws_col &&
	get_cursor_position(1) == sz.ws_row)
	{
		ft_putchar(key);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		ed->first_row--;
	}
	else
		ft_putchar(key);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	return (1);
}
