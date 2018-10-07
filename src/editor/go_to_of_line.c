/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   go_to_of_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 23:51:13 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 01:33:18 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	go_to_end_of_line(t_editor *ed)
{
	if (ed->cursor_str_pos < ft_strlen(ed->line))
	{
		tputs(tgoto(tgetstr("cv", NULL), 0, ed->first_row - 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, ed->prompt_size - 1), 1,
		ft_putchar);
		ft_putstr(ed->line);
		ed->cursor_str_pos = ft_strlen(ed->line);
		if (!((ft_strlen(ed->line) + ed->prompt_size - 1) % ed->ws_col))
			tputs(tgetstr("do", NULL), 1, ft_putchar);
	}
}

void	go_to_begin_of_line(t_editor *ed)
{
	if (ed->cursor_str_pos)
	{
		tputs(tgoto(tgetstr("cv", NULL), 0, ed->first_row - 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0,
		ed->prompt_size - 1), 1, ft_putchar);
		ed->cursor_str_pos = 0;
	}
}
