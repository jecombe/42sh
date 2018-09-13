/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   historic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:01:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:09:31 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	historic(t_editor *ed)
{
	int fd;

	go_to_begin_of_line(ed);
	delete_from_cursor_to_end(ed);
	if (UP_KEY)
		history_get(&(ed)->line, -1);
	else if (DOWN_KEY)
		history_get(&(ed)->line, 1);
	ft_putstr(ed->line);
	ed->cursor_str_pos = ft_strlen(ed->line);
}

void	fill_hist_list(t_hist *hist, char *line)
{
	t_hist *now;
	t_hist *new;

	(void)hist;
	(void)line;
	now = NULL;
	new = NULL;
/*	while (hist)
	{
		hist 
	}
	new = (t_hist*)malloc(sizeof(t_hist));*/
}
