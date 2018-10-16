/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   end_of_text.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 15:04:29 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 15:04:31 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void			end_of_text(t_editor *ed, e_prompt *prompt, char **line)
{
	if ((ed->last_row - get_cursor_position(1)) > 0)
		tputs(tgoto(tgetstr("DO", NULL), 0, ed->last_row -
		get_cursor_position(1)), 1, ft_putchar);
	ft_putchar('\n');
	display_prompt(PROMPT);
	ed->first_row = get_cursor_position(1);
	ed->last_row = ed->first_row;
	ed->cur_row = ed->first_row;
	ed->cur_col = get_cursor_position(0);
	ed->first_char = ed->cur_col;
	ed->last_char = ed->cur_col;
	ed->ret = *prompt == E_HDOC ? -3 : ed->ret;
	ft_strdel(&(ed->line));
	*prompt = PROMPT;
	ed->cursor_str_pos = 0;
}
