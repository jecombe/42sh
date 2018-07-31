/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   paste_clipboard.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/23 12:38:19 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/31 23:34:55 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

void	paste_clipboard(char **line, t_editor *ed)
{
	char tmp[ft_strlen(*line) + ft_strlen(ed->clipboard) + 1];

		//	printf("test0: %s\n", ed->clipboard);
	if (ed->clipboard)
	{
		if (*line)
		{
			ft_strncpy(tmp, *line, ed->cursor_str_pos);
			ft_strcat(tmp, ed->clipboard);
			ft_putstr(ed->clipboard);
			ft_strcat(tmp, *line + ed->cursor_str_pos);
			ft_putstr(*line + ed->cursor_str_pos);
			ft_strdel(line);
			*line = ft_strdup(tmp);
			//ft_putstr(ed->clipboard);
			ed->cursor_str_pos = ft_strlen(*line);
		}
		else
		{
			printf("test: %s\n", ed->clipboard);
			*line = ft_strdup(ed->clipboard);
			ft_putstr(*line);
			ed->cursor_str_pos = ft_strlen(*line);
		}
	}
}
