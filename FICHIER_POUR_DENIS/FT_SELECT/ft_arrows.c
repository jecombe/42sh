/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_arrows.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:23:54 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 00:46:23 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

static int		ft_up_and_down(char arrows, t_select **t, t_line *l, int y)
{
	if (arrows == 66 ? l->next : l->prev)
		l = arrows == 66 ? l->next : l->prev;
	else if (arrows == 66)
		l = (*t)->line;
	else
		while (l->next)
			l = l->next;
	l->cursor_inside = 1;
	if (y == 0 && l->y_pos > (*t)->ws.ws_row)
		(*t)->pose_min = ((*t)->nbl - 1 - (*t)->ws.ws_row + 1);
	else if (l->y_pos == y + 1 && l->y_pos >= (*t)->ws.ws_row + (*t)->pose_min)
		(*t)->pose_min++;
	else if (l->y_pos < (*t)->pose_min)
		(*t)->pose_min = l->y_pos;
	else
	{
		ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos, 1);
		ft_print_select(l, 0, (*t)->bp, 0);
		ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos + (*t)->bp, 0);
		return (0);
	}
	ft_print_params(&(*t));
	return (0);
}

static t_line	*ft_left_arrows(t_line *tmp, t_line *l, t_select *t)
{
	t_line	*ret;

	ret = NULL;
	while (tmp)
	{
		if (tmp->y_pos == l->y_pos && tmp->x_param_pos + 1 == l->x_param_pos)
			return (tmp);
		else if (tmp->y_pos + 1 == l->y_pos && l->x_param_pos == 0)
			ret = tmp;
		tmp = tmp->next;
	}
	if (!ret)
		while (l)
		{
			if (l->y_pos == t->nbl - 1)
			{
				if (ret)
					ret->x_param_pos < l->x_param_pos ? ret = l : 0;
				else
					ret = l;
			}
			l = l->next;
		}
	return (ret == NULL ? t->line : ret);
}

static t_line	*ft_search_lar(t_line *l, int arrows, t_select *t)
{
	t_line	*tp;
	t_line	*ret;

	tp = t->line;
	ret = NULL;
	if (arrows == 67)
		while (tp)
		{
			if (tp->y_pos == l->y_pos && tp->x_param_pos == l->x_param_pos + 1)
				return (tp);
			else if (tp->y_pos == l->y_pos + 1 && tp->x_param_pos == 0)
				ret = tp;
			tp = tp->next;
		}
	else
		ret = ft_left_arrows(tp, l, t);
	return (ret == NULL ? t->line : ret);
}

static void		ft_left_and_right(char arrows, t_select **t, t_line *l, int y)
{
	l = ft_search_lar(l, arrows, (*t));
	l->cursor_inside = 1;
	if (y == 0 && l->y_pos > (*t)->ws.ws_row)
	{
		(*t)->pose_min = (l->y_pos - (*t)->ws.ws_row + 1);
		ft_print_params(&(*t));
	}
	if (l->y_pos == y + 1 && l->y_pos >= (*t)->ws.ws_row + (*t)->pose_min)
	{
		(*t)->pose_min++;
		ft_print_params(&(*t));
	}
	else if (l->y_pos < (*t)->pose_min)
	{
		(*t)->pose_min = l->y_pos;
		ft_print_params(&(*t));
	}
	else
	{
		ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos, 1);
		ft_print_select(l, 0, (*t)->bp, 0);
		ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos + (*t)->bp, 0);
	}
}

int				ft_arrows(char arrows, t_select **t)
{
	t_line	*l;
	int		y;

	if (!(arrows == 65 || arrows == 66 || arrows == 67 || arrows == 68))
		return (1);
	l = (*t)->line;
	while (l->cursor_inside != 1)
		l = l->next;
	y = l->y_pos;
	l->cursor_inside = 0;
	ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos, 1);
	ft_print_select(l, 0, (*t)->bp, 0);
	ft_place_cursor(l->y_pos - (*t)->pose_min, l->x_char_pos + (*t)->bp, 0);
	if (arrows == 65 || arrows == 66)
		ft_up_and_down(arrows, &(*t), l, y);
	if (arrows == 67 || arrows == 68)
		ft_left_and_right(arrows, &(*t), l, y);
	return (1);
}
