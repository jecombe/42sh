/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 11:58:36 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 13:20:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

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

void			manage_init(t_shell **ed, int i, t_line *line)
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
		line->is_file = (*ed)->t.is_file ? (*ed)->t.is_file[i] - '0' : 0;
		line = line->next;
	}
	(*ed)->sel->bp = ft_search_big_param((*ed)->sel->line);
	(*ed)->sel->pose_min = 0;
	(*ed)->sel->ds = NULL;
	(*ed)->sel->ret = NULL;
	(*ed)->sel->ws = (*ed)->ws;
	(*ed)->sel->pbl = ft_params_by_line((*ed)->sel);
	(*ed)->sel->nbl = ft_count_line((*ed)->sel);
	(*ed)->sel->ws.ws_row -= (*ed)->sel->ws.ws_row <= (*ed)->sel->nbl +
		(*ed)->t.nb_line ? (*ed)->t.nb_line : 0;
	(*ed)->sel->nbp = ft_count_params((*ed)->sel->line);
}

void			ft_init_select(t_shell **ed)
{
	int		i;
	t_line	*line;

	i = -1;
	line = NULL;
	(*ed)->sel = malloc(sizeof(t_select));
	(*ed)->sel->line = NULL;
	if ((*ed)->t.elem)
	{
		manage_init(ed, i, line);
		i = (*ed)->sel->nbl;
		while (i > 0)
		{
			TERMCAP("sf");
			i--;
		}
		i = (*ed)->sel->nbl;
		while (i > 0)
		{
			TERMCAP("up");
			i--;
		}
	}
}
