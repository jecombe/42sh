/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   go_to_begin_of_line.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:47:20 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/09 23:53:26 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

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
