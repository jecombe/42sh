/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_window.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:18:49 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 08:43:05 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

int		clear_window(t_shell *sh, t_editor *ed)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	display_prompt(sh->pwd, g_save_home, sh->err, cut_pwd_dir(sh->pwd));
	if (sh->line)
		ft_putstr(sh->line);
	ed->last_row = get_cursor_position(1);
	ed->first_row = ed->last_row;
	return (0);
}
