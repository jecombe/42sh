/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   go_to_of_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 20:32:37 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 18:41:04 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	go_to_end_of_line(t_editor *ed)
{
	if (ed->cursor_str_pos < ft_strlen(ed->line))
	{
		tputs(tgoto(tgetstr("cv", NULL), 0, ed->last_row - 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, ed->last_char - 1), 1,
		ft_putchar);
		ed->cursor_str_pos = ft_strlen(ed->line);
		ed->cur_col = ed->last_char;
		ed->cur_row = ed->last_row;
	}
}

void	go_to_begin_of_line(t_editor *ed)
{
	if (ed->cursor_str_pos)
	{
		tputs(tgoto(tgetstr("cv", NULL), 0, ed->first_row - 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0,
		ed->first_char - 1), 1, ft_putchar);
		ed->cursor_str_pos = 0;
		ed->cur_col = ed->first_char;
		ed->cur_row = ed->first_row;
	}
}
