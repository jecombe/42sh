/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_from_cursor_to_end.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/23 11:54:31 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/31 23:34:47 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

void	delete_from_cursor_to_end(char **line, t_editor *ed)
{
	char tmp[ed->cursor_str_pos + 1];

	ft_bzero(tmp, sizeof(tmp));
	ft_putstr("\E[0J");
	if (!ed->cursor_str_pos)
	{
		if (line)
			ed->clipboard = ft_strdup(*line);
		ft_strdel(line);
	}
	else
	{
		ft_strncpy(tmp, *line, ed->cursor_str_pos);
		if (ed->clipboard)
			ft_strdel(&(ed->clipboard));
		ed->clipboard = ft_strdup(*line + ed->cursor_str_pos);
		if (line)
		ft_strdel(line);
		*line = ft_strdup(tmp);
	}
}
