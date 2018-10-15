/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   paste_line.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 20:34:38 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 21:17:38 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	add_paste_into_line(t_editor *ed)
{
	int		tmp_last_pos;
	char	tmp[ft_strlen(ed->line) + ft_strlen(ed->key) + 1];

	tmp_last_pos = ed->cursor_str_pos + ft_strlen(ed->key);
	if (ed->line)
	{
		ft_bzero(tmp, ft_strlen(ed->line) + ft_strlen(ed->key) + 1);
		ft_strncpy(tmp, ed->line, ed->cursor_str_pos);
		ft_strcat(tmp, ed->key);
		ft_strcat(tmp, ed->line + ed->cursor_str_pos);
		ft_strdel(&ed->line);
		ed->line = ft_strdup(tmp);
	}
	else
	{
		ft_strdel(&ed->line);
		ed->line = ft_strdup(ed->key);
	}
	ft_putstr(ed->line + ed->cursor_str_pos);
	ed->last_char = get_cursor_position(0);
	ed->last_row = get_cursor_position(1);
	ed->cursor_str_pos = ft_strlen(ed->line);
	while (ed->cursor_str_pos != tmp_last_pos)
		move_cursor_left(ed);
	if (ed->cur_col == ed->ws_col && ed->cur_row == ed->ws_row)
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
}
