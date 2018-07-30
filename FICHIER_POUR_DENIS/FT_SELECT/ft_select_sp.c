/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select_sp.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/25 12:37:39 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/25 12:39:18 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

void		ft_decremente_select(int select, t_select **t)
{
	t_line		*line;

	line = (*t)->line;
	while (line)
	{
		if (line->select > select)
			line->select--;
		line = line->next;
	}
	(*t)->select_max--;
}

static void	ft_highlight(t_line *l, t_select *t)
{
	if (l->y_pos - t->pose_min)
		tputs(tgoto(tgetstr("DO", NULL), 0, l->y_pos - t->pose_min),
		1, ft_outc);
	if (l->x_char_pos)
		tputs(tgoto(tgetstr("RI", NULL), 0, l->x_char_pos), 1, ft_outc);
	ft_print_select(l, 0, t->bp, 1);
	if (l->y_pos - t->pose_min)
		tputs(tgoto(tgetstr("UP", NULL), 0, l->y_pos - t->pose_min),
		1, ft_outc);
	if (l->x_char_pos || t->bp)
		tputs(tgoto(tgetstr("LE", NULL), 0, l->x_char_pos + t->bp), 1, ft_outc);
}

int			ft_select_sp(t_select **t)
{
	t_line		*line;

	line = (*t)->line;
	while (line->cursor_inside == 0)
		line = line->next;
	if (line->select == 0)
		line->select = ++(*t)->select_max;
	else
	{
		ft_decremente_select(line->select, &(*t));
		line->select = 0;
	}
	ft_highlight(line, (*t));
	return (2);
}
