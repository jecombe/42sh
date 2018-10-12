/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ctrl.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 23:45:27 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 18:33:11 by dewalter    ###    #+. /#+    ###.fr     */
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

int		clear_window(t_editor *ed, e_prompt prompt)
{
	size_t	cursor_str_pos_tmp;

	cursor_str_pos_tmp = ed->cursor_str_pos;
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	display_prompt(prompt);
	ed->first_row = get_cursor_position(1);
	ed->first_char = get_cursor_position(0);
	if (ed->line)
		ft_putstr(ed->line);
	ed->cur_col = get_cursor_position(0);
	ed->cur_row = get_cursor_position(1);
	ed->last_row = get_cursor_position(1);
	ed->last_char = get_cursor_position(0);
	ed->cursor_str_pos = ft_strlen(ed->line);
	while (cursor_str_pos_tmp != ed->cursor_str_pos)
		move_cursor_left(ed);
	return (0);
}

void	end_of_text(t_editor *ed, e_prompt *prompt, char **line)
{
	if ((ed->last_row - get_cursor_position(1)) > 0)
		tputs(tgoto(tgetstr("DO", NULL), 0, ed->last_row -
		get_cursor_position(1)), 1, ft_putchar);
	ft_putchar('\n');
	display_prompt(PROMPT);
	ed->last_row = get_cursor_position(1);
	ed->first_row = ed->last_row;
	ed->ret = *prompt == E_HDOC ? -3 : ed->ret;
	ft_strdel(&(ed->line));
	*prompt = PROMPT;
	ed->cursor_str_pos = 0;
}

void	delete_from_cursor_to_end(t_editor *ed)
{
	char tmp[ed->cursor_str_pos + 1];

	ft_strdel(&ed->clipboard);
	ft_bzero(tmp, sizeof(tmp));
	ft_putstr("\E[0J");
	if (!ed->cursor_str_pos)
	{
		ed->clipboard = ft_strdup(ed->line);
		ft_strdel(&(ed->line));
	}
	else
	{
		ft_strncpy(tmp, ed->line, ed->cursor_str_pos);	
		ed->clipboard = ft_strdup(ed->line + ed->cursor_str_pos);
		ft_strdel(&(ed->line));
		ed->line = ft_strdup(tmp);
	}
}
