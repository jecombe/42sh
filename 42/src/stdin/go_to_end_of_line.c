/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   go_to_end_of_line.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 06:27:22 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 23:27:44 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

void	go_to_end_of_line(t_editor *ed)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (ed->cursor_str_pos < ft_strlen(ed->line))
	{
		tputs(tgoto(tgetstr("cv", NULL), 0, ed->first_row - 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, ed->prompt_size - 1), 1, ft_putchar);
		ft_putstr(ed->line);
		ed->cursor_str_pos = ft_strlen(ed->line);
		if (!((ft_strlen(ed->line) + ed->prompt_size - 1) % sz.ws_col))
			tputs(tgetstr("do", NULL), 1, ft_putchar);
	}
}
