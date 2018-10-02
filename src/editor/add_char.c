/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_char.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 10:42:22 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 17:39:41 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		add_char_into_line_2(char key, t_editor *ed)
{
	char tmp[ft_strlen(ed->line) + 2];

	ft_bzero(tmp, sizeof(tmp));
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ft_strncpy(tmp, ed->line, ed->cursor_str_pos);
	tmp[ed->cursor_str_pos - 1] = key;
	ft_strcat(tmp, ed->line + ed->cursor_str_pos - 1);
	ft_strdel(&(ed->line));
	ed->line = ft_strdup(tmp);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, ed->line + ed->cursor_str_pos,
	ft_strlen(ed->line + ed->cursor_str_pos));
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

static void		add_char_into_line_1(char key, t_editor *ed, struct winsize sz)
{
	if (!((ft_strlen(ed->line) + ed->prompt_size) % sz.ws_col))
	{
		ft_putchar(key);
		//if (!(get_cursor_position(0) % sz.ws_col))
		if (!(ed->cur_pos % sz.ws_col))
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		ed->last_row++;
	}
	//else if (!(get_cursor_position(0) % sz.ws_col))
	else if (!(ed->cur_pos % sz.ws_col))
	{
		ft_putchar(key);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	}
	else
		ft_putchar(key);
}

void			add_char_into_line(char key, t_editor *ed)
{
	char *cursor_reset;
	t_sz sz;
	ed->cursor_str_pos++;
	ioctl(0, TIOCGWINSZ, &sz);
	ed->cur_pos = !get_cursor_position(0) ? ed->cur_pos + 1 : get_cursor_position(0);
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	if (ed->line && (!((ft_strlen(ed->line) + ed->prompt_size) % sz.ws_col) &&
	ed->last_row == sz.ws_row))
	{
		//if (!((get_cursor_position(0)) % sz.ws_col))
		if (!(ed->cur_pos % sz.ws_col))
		{
			ft_putchar(key);
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
		else
			ft_putchar(key);
		cursor_reset = cursor_position_escape_sequence(1, 0);
		tputs(tgoto(tgetstr("DO", NULL), 0, (ed->last_row -
		get_cursor_position(1))), 1, ft_putchar);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		reset_cursor_position_escape_sequence(&cursor_reset);
		ed->first_row--;
	}
	else
		add_char_into_line_1(key, ed, sz);
	add_char_into_line_2(key, ed);
}

int				add_char_to_line(char key, t_editor *ed)
{
	t_sz sz;
	ioctl(0, TIOCGWINSZ, &sz);
	ed->cursor_str_pos++;
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	//dprintf(2, "cur_pos: %zu\n", get_cursor_position(0));
	if (get_cursor_position(0) == sz.ws_col &&
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
