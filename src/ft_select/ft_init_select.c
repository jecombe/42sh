/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/02 20:48:47 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 11:37:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

static t_line	*ft_init_begin(t_line **line, char *av, int inside)
{
	t_line	*after;

	after = malloc(sizeof(t_line));
	(*line) = after;
	after->prev = NULL;
	after->next = NULL;
	after->cursor_inside = inside;
	after->x_char_pos = 0;
	after->ds = 0;
	after->x_param_pos = 0;
	after->y_pos = 0;
	after->elem = ft_strdup(av);
	after->is_file = ft_is_file(av);
	return (after);
}

void			ft_init_select(t_editor **ed)
{
	int		i;
	t_line	*now;
	t_line	*line;

	i = -1;
///	printf("ENTER INSIDE INIT SELECT\n");
///	sleep(1);
	if ((*ed)->t.elem)
	{
///		printf("3000\n");
///		sleep(1);
		(*ed)->sel = malloc(sizeof(t_select));
		(*ed)->sel->line = NULL;
		while ((*ed)->t.elem[++i])
		{
			if ((*ed)->sel->line)
				ft_first_sort(&(*ed)->sel->line, (*ed)->t.elem[i], 0);
			else
				now = ft_init_begin(&(*ed)->sel->line, (*ed)->t.elem[i], 0);
		}
		i = 0;
		line = (*ed)->sel->line;
///		printf("3001\n");
///		sleep(1);
		while (line)
		{
			if (i == (*ed)->tabu)
				line->cursor_inside = 1;
			i++;
			line = line->next;
		}
///		printf("3002\n");
///		sleep(1);
		(*ed)->sel->bp = ft_search_big_param((*ed)->sel->line);
		(*ed)->sel->pose_min = 0;
		(*ed)->sel->ds = NULL;
		(*ed)->sel->ret = NULL;
		ft_get_size_term(&(*ed)->sel->ws, &(*ed)->sel, 1);
		(*ed)->sel->pbl = ft_params_by_line((*ed)->sel);
		(*ed)->sel->nbl = ft_count_line((*ed)->sel);
		(*ed)->sel->nbp = ft_count_params((*ed)->sel->line);
///		printf("3003\n");
///		sleep(1);
	}
///		printf("3004\n");
///		sleep(1);
}
