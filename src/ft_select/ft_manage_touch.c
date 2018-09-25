/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_touch.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:28:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 03:37:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

int			ft_attrib_line(t_select **t)
{
	t_line		*line;

	line = (*t)->line;
	while (line->cursor_inside == 0)
		line = line->next;
	(*t)->ret = ft_strdup(line->elem);
	return (0);
}

int			ft_manage_touch(char *ret, t_select **t, int *place)
{
	if ((ret[0] == 27 && ret[1] == 91) ||
	(ret[0] == 9 && ret[1] == 0))
	{
		ft_arrows(ret[0] == 9 ? 66 : ret[2], &(*t), place);
		return (ft_attrib_line(t) + 1);
	}
	else if (ret[0] == 10)
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		return (ft_attrib_line(t) + 4);
	}
	return (-1);
}
