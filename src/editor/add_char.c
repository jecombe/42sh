/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_char.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 10:42:22 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 20:48:42 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		add_char_into_line_2(char key, t_editor *ed)
{
	char tmp[ft_strlen(ed->line) + 2];

	ed->cursor_str_pos++;
	ft_bzero(tmp, ft_strlen(ed->line) + 2);
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
	ed->cur_col++;
	ed->last_char++;
}

static void		add_char_into_line_1(char key, t_editor *ed)
{
	if (ed->last_char == ed->ws_col)
	{
		ed->last_char = 0;
		ft_putchar(key);
		if (ed->cur_col == ed->ws_col)
		{
			ed->cur_col = 0;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			ed->cur_row = ed->cur_row == ed->ws_row ?
			ed->cur_row : ed->cur_row + 1;
		}
		ed->last_row = ed->last_row == ed->ws_row ?
		ed->last_row : ed->last_row + 1;
	}
	else if (ed->cur_col == ed->ws_col)
	{
		ed->cur_col = 0;
		ft_putchar(key);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		ed->cur_row = ed->cur_row == ed->ws_row ? ed->cur_row : ed->cur_row + 1;
	}
	else
		ft_putchar(key);
}

void			add_char_into_line(char key, t_editor *ed)
{
	char *cursor_reset;

	tputs(tgetstr("im", NULL), 1, ft_putchar);
	if (ed->line && ed->last_char == ed->ws_col && ed->last_row == ed->ws_row)
	{
		if (ed->cur_col == ed->ws_col)
		{
			ed->cur_col = 0;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			ed->cur_row = ed->cur_row == ed->ws_row ?
			ed->cur_row : ed->cur_row + 1;
		}
		ft_putchar(key);
		cursor_reset = cursor_position_escape_sequence(1, -1, ed);
		tputs(tgoto(tgetstr("DO", NULL), 0,
		(ed->last_row - ed->cur_row)), 1, ft_putchar);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		reset_cursor_position_escape_sequence(&cursor_reset);
		ed->first_row--;
		ed->last_char = 0;
		ed->cur_row--;
	}
	else
		add_char_into_line_1(key, ed);
	add_char_into_line_2(key, ed);
}

void			add_char_to_line(char key, t_editor *ed)
{
	ed->cursor_str_pos++;
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	if (ed->cur_col == ed->ws_col && ed->cur_row != ed->ws_row)
	{
		ed->cur_col = 0;
		ed->last_char = 0;
		ft_putchar(key);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		ed->cur_row = ed->cur_row == ed->ws_row ? ed->cur_row : ed->cur_row++;
		ed->last_row = ed->last_row == ed->ws_row ? ed->ws_row : ed->last_row++;
	}
	else if (ed->cur_col == ed->ws_col && ed->cur_row == ed->ws_row)
	{
		ed->cur_col = 0;
		ed->last_char = 0;
		ft_putchar(key);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		ed->last_row = ed->last_row == ed->ws_row ? ed->ws_row : ed->last_row++;
		ed->first_row--;
	}
	else
		ft_putchar(key);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ed->cur_col++;
	ed->last_char++;
}

int				print_key(t_editor **ed)
{
	if (ft_strlen((*ed)->key) == 1)
	{
		if ((*ed)->cursor_str_pos == ft_strlen((*ed)->line))
		{
			add_char_to_line((*ed)->key[0], *ed);
			return (1);
		}
		else
			add_char_into_line((*ed)->key[0], *ed);
	}
	else
		add_paste_into_line(*ed);
	return (EXIT_SUCCESS);
}
