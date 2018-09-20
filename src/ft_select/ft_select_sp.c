/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select_sp.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/25 12:37:39 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 15:29:22 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

int			ft_select_sp(t_select **t)
{
	t_line		*line;

	line = (*t)->line;
	while (line->cursor_inside == 0)
		line = line->next;
	(*t)->ret = line->elem;
	return (4);
}
