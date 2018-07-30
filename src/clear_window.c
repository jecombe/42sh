/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_window.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:18:49 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 07:43:00 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

int		clear_window(char *line, t_editor *ed, e_prompt prompt)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	display_prompt(find_var_string(g_env, "HOME", 0), prompt);
	if (line)
		ft_putstr(line);
	ed->last_row = get_cursor_position(1);
	ed->first_row = ed->last_row;
	return (0);
}
