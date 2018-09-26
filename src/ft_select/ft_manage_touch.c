/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_touch.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:28:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 10:12:33 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

int			replace_line_after_tab(t_editor **ed)
{
	int		i;

	i = -1;
	if ((*ed)->t.cmd)
	{
		(*ed)->cursor_str_pos = 0;
		while ((*ed)->t.cmd[++i] && i < (*ed)->t.nb_char - 1)
		{
			(*ed)->cursor_str_pos += ft_strlen((*ed)->t.cmd[i]);
		}
		ft_strdel(&(*ed)->t.cmd[(*ed)->t.nb_char - 1]);
		(*ed)->t.cmd[(*ed)->t.nb_char - 1] = (*ed)->sel->ret;
		(*ed)->cursor_str_pos += ft_strlen((*ed)->sel->ret);
		ft_concat_tab_to_str((*ed)->t.cmd, &(*ed)->line);
	}
	else//CA ME PARAIT CHELOU X)
	{
		(*ed)->line = ft_strdup((*ed)->sel->ret);
		(*ed)->cursor_str_pos += (*ed)->line ? ft_strlen((*ed)->line) : 0;
	}
//	ft_strdel(&(*ed)->sel->ret);
	return (0);
}

int			ft_attrib_line(t_editor **ed)
{
	t_line		*line;

	line = (*ed)->sel->line;
	while (line->cursor_inside == 0)
		line = line->next;
	(*ed)->sel->ret = ft_strdup(line->elem);
	replace_line_after_tab(ed);
	return (0);
}

int			ft_manage_touch(t_editor **ed)
{
	if (((*ed)->key[0] == 27 && (*ed)->key[1] == 91) ||
			((*ed)->key[0] == 9 && (*ed)->key[1] == 0))
	{
		ft_arrows((*ed)->key[0] == 9 ? 66 : (*ed)->key[2], &(*ed)->sel, &(*ed)->tabu);
		return (ft_attrib_line(ed) + 1);
	}
	else if ((*ed)->key[0] == 10)
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		return (ft_attrib_line(ed) + 4);
	}
	return (-1);
}
