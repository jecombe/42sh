/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_from_cursor_to_end.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/23 11:54:31 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/23 12:38:09 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	delete_from_cursor_to_end(t_shell *sh, t_editor *ed)
{
	char tmp[ed->cursor_str_pos + 1];

	ft_bzero(tmp, sizeof(tmp));
	ft_putstr("\E[0J");
	ft_strncpy(tmp, sh->line, ed->cursor_str_pos);
	if (sh->clipboard)
		ft_strdel(&(sh->clipboard));
	sh->clipboard = ft_strdup(sh->line + ed->cursor_str_pos);
	ft_strdel(&(sh->line));
	sh->line = ft_strdup(tmp);
}
