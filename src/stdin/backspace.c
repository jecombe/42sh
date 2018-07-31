/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backspace.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:10:17 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/31 23:34:45 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

int		backspace(t_editor *ed, char **line)
{
	char tmp[ft_strlen(*line)];
	char *cursor_reset;

	ioctl(0, TIOCGWINSZ, &sz);
	bzero(tmp, sizeof(tmp));
	ed->cursor_str_pos--;
	if (get_cursor_position(0) == 1)
	{
		tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	ft_strncpy(tmp, *line, ed->cursor_str_pos);
	ft_strcat(tmp, *line + (ed->cursor_str_pos + 1));
	ft_strdel(&*line);
	if (ft_strlen(tmp))
		*line = ft_strdup(tmp);
	cursor_reset = cursor_position_escape_sequence(0, 0);
	ft_putstr("\E[0J");
	ft_putstr(*line + ed->cursor_str_pos);
	reset_cursor_position_escape_sequence(&cursor_reset);
	if (!((ft_strlen(*line) + ed->prompt_size) % sz.ws_col))
		ed->last_row--;
	return (0);
}
