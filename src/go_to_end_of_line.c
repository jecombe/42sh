/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   go_to_end_of_line.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 06:27:22 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 22:32:20 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	go_to_end_of_line(t_editor *ed, char *line)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (ed->cursor_str_pos < ft_strlen(line))
	{
		tputs(tgoto(tgetstr("cv", NULL), 0, ed->first_row - 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, ed->prompt_size - 1), 1, ft_putchar);
		ft_putstr(line);
		ed->cursor_str_pos = ft_strlen(line);
		if (!((ft_strlen(line) + ed->prompt_size - 1) % sz.ws_col))
			tputs(tgetstr("do", NULL), 1, ft_putchar);
	}
}
