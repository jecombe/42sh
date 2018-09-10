/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   end_of_text.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 08:32:55 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/09 23:53:21 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

void	end_of_text(t_editor *ed, e_prompt *prompt, char **line)
{
	char buf[4096];

	if ((ed->last_row - get_cursor_position(1)) > 0)
		tputs(tgoto(tgetstr("DO", NULL), 0, ed->last_row -
		get_cursor_position(1)), 1, ft_putchar);
	ft_putchar('\n');
	getcwd(buf, sizeof(buf));
	display_prompt(find_env_var(g_env, "HOME", 0), PROMPT);
	ed->last_row = get_cursor_position(1);
	ed->first_row = ed->last_row;
	if (ed->line)
		ft_strdel(&(ed->line));
	if (*line)
		ft_strdel(line);
	*prompt = PROMPT;
	ed->cursor_str_pos = 0;
}
