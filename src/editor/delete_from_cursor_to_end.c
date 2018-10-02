/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_from_cursor_to_end.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/23 11:54:31 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:09:27 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	delete_from_cursor_to_end(t_editor *ed)
{
	char tmp[ed->cursor_str_pos + 1];

	ft_strdel(&ed->clipboard);
	ft_bzero(tmp, sizeof(tmp));
	ft_putstr("\E[0J");
	if (!ed->cursor_str_pos)
	{
		ed->clipboard = ft_strdup(ed->line);
		ft_strdel(&(ed->line));
	}
	else
	{
		ft_strncpy(tmp, ed->line, ed->cursor_str_pos);	
		ed->clipboard = ft_strdup(ed->line + ed->cursor_str_pos);
		ft_strdel(&(ed->line));
		ed->line = ft_strdup(tmp);
	}
}
