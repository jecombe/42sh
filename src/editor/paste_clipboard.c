/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   paste_clipboard.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 15:40:27 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 15:40:30 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		paste_clipboard_into_line(t_editor *ed)
{
	char tmp[ft_strlen(ed->line) + ft_strlen(ed->clipboard) + 1];

	bzero(tmp, ft_strlen(ed->line) + ft_strlen(ed->clipboard) + 1);
	ft_strncpy(tmp, ed->line, ed->cursor_str_pos);
	ft_strcat(tmp, ed->clipboard);
	ft_strcat(tmp, ed->line + ed->cursor_str_pos);
	ft_putstr(ed->clipboard);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_putstr(ed->line + ed->cursor_str_pos);
	ed->cursor_str_pos += ft_strlen(ed->clipboard);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	ft_strdel(&(ed->line));
	ed->line = ft_strdup(tmp);
}

void			paste_clipboard(t_editor *ed)
{
	if (ed->clipboard)
	{
		if (ed->cursor_str_pos == ft_strlen(ed->line))
		{
			ed->line = ft_strjoin_free(ed->line, ed->clipboard);
			ed->cursor_str_pos = ft_strlen(ed->line);
			ft_putstr(ed->clipboard);
			if (get_cursor_position(0) == ed->ws_col &&
				get_cursor_position(1) != ed->ws_row)
			{
				tputs(tgetstr("do", NULL), 1, ft_putchar);
				ed->last_row = get_cursor_position(1);
			}
		}
		else
			paste_clipboard_into_line(ed);
	}
}
