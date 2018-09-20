/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/02 20:48:47 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 17:02:53 by gmadec      ###    #+. /#+    ###.fr     */
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

void			ft_init_select(t_select **sel, char **av, int index)
{
	int		i;
	t_line	*now;
	t_line	*line;

	i = -1;
	if (av[1])
	{
		*sel = malloc(sizeof(t_select));
		(*sel)->line = NULL;
		while (av[++i])
		{
			if ((*sel)->line)
				ft_first_sort(&(*sel)->line, av[i], 0);
			else
				now = ft_init_begin(&(*sel)->line, av[i], 0);
		}
		i = 0;
		line = (*sel)->line;
		while (line)
		{
			if (i == index)
				line->cursor_inside = 1;
			i++;
			line = line->next;
		}
		(*sel)->bp = ft_search_big_param((*sel)->line);
		(*sel)->pose_min = 0;
		(*sel)->ds = NULL;
		(*sel)->ret = NULL;
	}
}
