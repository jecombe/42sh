/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_touch.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:28:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 01:20:30 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"
#include <stdio.h>

static void		ft_highlightds(int len, t_line *l, t_select *t, int i)
{
	ft_place_cursor(l->y_pos - t->pose_min, l->x_char_pos, 1);
	ft_print_select(l, 0, t->bp, 0);
	ft_place_cursor(l->y_pos - t->pose_min, l->x_char_pos + t->bp, 0);
	ft_place_cursor(l->y_pos - t->pose_min, l->x_char_pos + i, 1);
	(void)len;
	(void)t;
	ft_putstr_fd(BOLD, 2);
	tputs(tgetstr("mr", NULL), 1, ft_outc);
	ft_putstr_fd(t->ds, 2);
	tputs(tgetstr("me", NULL), 1, ft_outc);
	ft_putstr_fd(END, 2);
	ft_place_cursor(l->y_pos - t->pose_min, l->x_char_pos + len + i, 0);
}

static int		ft_searchinword(char *str, int begin, t_select *t)
{
	int		i;
	char	*tmp;
	int		len;

	if ((int)ft_strlen(str) >= (int)ft_strlen(t->ds) + begin)
	{
		tmp = ft_strsub(str, begin, ft_strlen(t->ds));
		i = 0;
		len = ft_strlen(str);
		if (ft_strcmp(t->ds, tmp) == 0)
		{
			ft_strdel(&tmp);
			return (1);
		}
		ft_strdel(&tmp);
	}
	return (0);
}

static void		ft_managetds(t_select **t, char ret)
{
	char		*tmp;
	size_t		i;

	i = -1;
	tmp = NULL;
	if ((*t)->ds)
	{
		tmp = ft_strdup((*t)->ds);
		ft_strdel(&(*t)->ds);
		(*t)->ds = malloc(sizeof(char) * (int)ft_strlen(tmp) + 2);
		while (tmp[++i])
			(*t)->ds[i] = tmp[i];
		(*t)->ds[i++] = ret;
		(*t)->ds[i] = '\0';
		ft_strdel(&tmp);
	}
	else
	{
		(*t)->ds = malloc(sizeof(char) * 1 + 1);
		(*t)->ds[0] = ret;
		(*t)->ds[1] = '\0';
	}
}

static int		ft_manageds(t_select **t, int i)
{
	t_line	*l;
	t_line	*b;

	l = (*t)->line;
	while (l)
	{
		if (ft_searchinword(l->elem, i, *t) == 1)
		{
			b = (*t)->line;
			while (b->cursor_inside != 1)
				b = b->next;
			b->cursor_inside = 0;
			ft_place_cursor(b->y_pos - (*t)->pose_min, b->x_char_pos, 1);
			ft_print_select(b, 0, (*t)->bp, 0);
			ft_place_cursor(b->y_pos - (*t)->pose_min,
			b->x_char_pos + (*t)->bp, 0);
			l->cursor_inside = 1;
			ft_highlightds((int)ft_strlen((*t)->ds), l, (*t), i);
			return (-1);
		}
		l = l->next;
	}
	return (0);
}

int				ft_searchdyn(t_select **t, char ret)
{
	int		i;

	i = -1;
	ft_managetds(&(*t), ret);
	while (++i < (*t)->bp && i != -101)
		if (ft_manageds(&(*t), i) == -1)
			i = -102;
	if (ft_strlen((*t)->ds) > 1 && i != -101)
	{
		ft_unhighlightds(&(*t));
		return (ft_searchdyn(&(*t), ret));
	}
	return (i == -101 ? 1 : 0);
}
