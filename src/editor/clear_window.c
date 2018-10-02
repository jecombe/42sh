/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_window.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:18:49 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:30:11 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		clear_window(t_editor *ed, e_prompt prompt)
{
	int cursor_str_pos_tmp;

	cursor_str_pos_tmp = ed->cursor_str_pos;
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
//	display_prompt(find_env_var(g_env, "HOME", 0), prompt);
	display_prompt(prompt);
	ed->first_row = get_cursor_position(1);
	if (ed->line)
		ft_putstr(ed->line);
	ed->last_row = get_cursor_position(1);
	ed->cursor_str_pos = ft_strlen(ed->line);
	while (cursor_str_pos_tmp != (int)ed->cursor_str_pos)
		move_cursor_left(ed);
	return (0);
}
