/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_del_maillon.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 02:46:52 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/29 04:46:28 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

void	ft_norme2(t_select **t)
{
	ft_strdel(&(*t)->line->elem);
	free((*t)->line);
	free((*t));
	*t = NULL;
	tputs(tgetstr("up", NULL), 1, ft_outc);
	exit(ft_disable_raw(0, &(*t)));
}

void	ft_norme1(t_line **line, t_line *tmp, t_select **t)
{
	if ((*line)->next && (*line)->prev)
	{
		tmp = (*line)->prev;
		*line = (*line)->next;
		tmp->next = *line;
		(*line)->prev = tmp;
	}
	else if ((*line)->next)
	{
		*line = (*line)->next;
		(*t)->line = *line;
		(*line)->prev = NULL;
	}
	else if ((*line)->prev)
	{
		*line = (*line)->prev;
		(*line)->next = NULL;
	}
	else if (!(*line)->next && !(*line)->prev)
		ft_norme2(&(*t));
}

int		ft_del_maillon(t_select **t)
{
	t_line		*line;
	t_line		*dead;
	t_line		*tmp;

	line = (*t)->line;
	while (line->cursor_inside == 0)
		line = line->next;
	if (line->select > 0)
		ft_decremente_select(line->select, &(*t));
	dead = line;
	tmp = NULL;
	ft_norme1(&line, tmp, &(*t));
	if (*t)
	{
		line->cursor_inside = 1;
		ft_strdel(&dead->elem);
		free(dead);
		dead = NULL;
		(*t)->bp = ft_search_big_param((*t)->line);
	}
	return (0);
}
