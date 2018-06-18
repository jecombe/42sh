/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_touch.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:28:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 00:53:19 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"
#include <stdio.h>

void		ft_unhighlightds(t_select **t)
{
	t_line		*l;

	l = (*t)->line;
	while (l->cursor_inside == 0)
		l = l->next;
	ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos, 1);
	ft_print_select(l, 0, (*t)->bp, 0);
	ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos + (*t)->bp, 0);
	ft_strdel(&(*t)->ds);
}

int			ft_manage_touch(char **ret, t_select **t)
{
	if ((*ret)[0] >= 33 && (*ret)[0] <= 126 && (*ret)[1] == 0)
	{
		if (ft_searchdyn(&(*t), (*ret)[0]) == 0 && (*t)->ds)
			ft_strdel(&(*t)->ds);
		return (1);
	}
	else if ((*t)->ds && (*ret)[0] != -1)
		ft_unhighlightds(&(*t));
	if ((*ret)[0] == 27 && (*ret)[1] == 0)
	{
		ft_strdel(&(*ret));
		exit(ft_disable_raw(0, &(*t)));
	}
	else if (((*ret)[0] == 27 && (*ret)[1] == 91) ||
	((*ret)[0] == 9 && (*ret)[1] == 0))
		return (ft_arrows((*ret)[0] == 9 ? 67 : (*ret)[2], &(*t)));
	else if ((*ret)[0] == 32 && (*ret)[1] == 0)
		return (ft_select_sp(&(*t)));
	else if ((((*ret)[0] == 127 && (*ret)[1] == 0)) ||
	((*ret)[0] == 126 && (*ret)[1] == 0 && (*ret)[2] == 51 && (*ret)[3] == 0))
		return (ft_del_maillon(&(*t)));
	else if ((*ret)[0] == 13)
		return (4);
	return (-1);
}
