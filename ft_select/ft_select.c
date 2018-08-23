/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 04:39:32 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/23 04:40:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/ft_select.h"

static char		*ft_print_final(t_select **t, int *line)
{
	t_line		*tmp;
	int			i;

	i = 1;
	tputs(tgetstr("cd", NULL), 1, ft_outc);
	if (*t)
	{*line = (*t)->nbl;
		while ((*t)->select_max >= i)
		{
			tmp = (*t)->line;
			while (tmp)
			{
				if (tmp->select == i)
				{
				//	if (i > 1)
				//		ft_putchar(' ');
					return(ft_strdup(tmp->elem));
					i++;
				}
				tmp = tmp->next;
			}
		}
	}
	return (0);
}

static int		ft_refresh(t_select *t, int ret, t_ws verif)
{
	if (((ret == 0 || verif.ws_col != t->ws.ws_col)) ||
	g_sign == 1 ||
	t->ws.ws_row != verif.ws_row)
		return (t->bp > t->ws.ws_col ? 2 : 1);
	return (0);
}

int				ft_test(t_select **sel, int ret)
{
	char		*entry;
	t_ws		verif;
	int			refresh;

	refresh = 0;
	entry = NULL;
	ft_get_size_term(&verif, &(*sel), 2);
	while ((*sel && ret != 4) || ret == 0)
	{
		ft_get_size_term(&(*sel)->ws, &(*sel), 2);
		refresh = ft_refresh((*sel), ret, verif);
		if (refresh == 1)
		{
			g_sign = 0;
			ft_get_size_term(&verif, &(*sel), 2);
			ft_print_params(&(*sel));
		}
		refresh == 2 ? ft_putstr_fd("\E[0J", 2) : 0;
		ret = ft_manage_entry(&entry, &(*sel));
		entry ? ft_strdel(&entry) : 0;
	}
	return (0);
}

char			*ft_select(char **av, int *line)
{
	t_select	*sel;
	int			ret;
	t_ws		verif;
	char		*test = NULL;

	ret = 0;
	g_sign = 1;
	if (!av)
		return (0);
	ft_enable_raw(&sel);
	ft_init_select(&sel, av);
	ft_get_size_term(&verif, &sel, 2);
	ft_test(&sel, ret);
	test = ft_print_final(&sel, line);
	ft_disable_raw(0, &sel);
	return (test);
}
