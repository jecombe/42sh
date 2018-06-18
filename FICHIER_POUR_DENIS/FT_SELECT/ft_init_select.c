/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/02 20:48:47 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/02 17:56:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"
#include <stdio.h>

static t_line	*ft_init_begin(t_line **line, char *av)
{
	t_line	*after;

	after = malloc(sizeof(t_line));
	(*line) = after;
	after->prev = NULL;
	after->next = NULL;
	after->cursor_inside = 0;
	after->x_char_pos = 0;
	after->ds = 0;
	after->x_param_pos = 0;
	after->y_pos = 0;
	after->elem = ft_strdup(av);
	after->is_file = ft_is_file(av);
	after->select = 0;
	return (after);
}

void			ft_init_select(t_select **sel, char **av)
{
	int		i;
	t_line	*now;

	i = 0;
	if (av[1])
	{
		*sel = malloc(sizeof(t_select));
		(*sel)->line = NULL;
		(*sel)->select_max = 0;
		while (av[++i])
		{
			if ((*sel)->line)
				ft_first_sort(&(*sel)->line, av[i]);
			else
				now = ft_init_begin(&(*sel)->line, av[i]);
		}
		(*sel)->line->cursor_inside = 1;
		(*sel)->bp = ft_search_big_param((*sel)->line);
		(*sel)->pose_min = 0;
		(*sel)->ds = NULL;
	}
}
