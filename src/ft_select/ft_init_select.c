/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 11:58:36 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 09:52:44 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/02 20:48:47 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 11:52:57 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

static t_line	*ft_init_begin(t_line **line, char *av)
{
	t_line	*after;

	after = malloc(sizeof(t_line));
	(*line) = after;
	after->prev = NULL;
	after->next = NULL;
	after->x_char_pos = 0;
	after->ds = 0;
	after->x_param_pos = 0;
	after->y_pos = 0;
	after->elem = ft_strdup(av);
	return (after);
}

void			manage_init(t_editor **ed, int i, t_line *line)
{
	while ((*ed)->t.elem[++i])
	{
		if ((*ed)->sel->line)
			ft_first_sort(&(*ed)->sel->line, (*ed)->t.elem[i]);
		else
			ft_init_begin(&(*ed)->sel->line, (*ed)->t.elem[i]);
	}
	i = -1;
	line = (*ed)->sel->line;
	while (line)
	{
		line->cursor_inside = ++i == (*ed)->tabu ? 1 : 0;
		line = line->next;
		i++;
	}
	(*ed)->sel->bp = ft_search_big_param((*ed)->sel->line);
	(*ed)->sel->pose_min = 0;
	(*ed)->sel->ds = NULL;
	(*ed)->sel->ret = NULL;
	ft_get_size_term(&(*ed)->sel->ws, &(*ed)->sel, 1);
	(*ed)->sel->pbl = ft_params_by_line((*ed)->sel);
	(*ed)->sel->nbl = ft_count_line((*ed)->sel);
	(*ed)->sel->nbp = ft_count_params((*ed)->sel->line);
}

void			ft_init_select(t_editor **ed)
{
	int		i;
	t_line	*line;
	DIR		*dir;
	char	*pwd;
	char	**file;

	file = NULL;
	i = -1;
	line = NULL;
	(*ed)->sel = malloc(sizeof(t_select));
	(*ed)->sel->line = NULL;
	if ((*ed)->t.elem)
		manage_init(ed, i, line);
}
