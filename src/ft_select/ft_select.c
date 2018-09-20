/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 15:53:31 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

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

int			ft_select(char **av, char **line, int *index)
{
	t_select	*sel;
	int			ret;
	t_ws		verif;

	ret = 0;
	tputs(tgetstr("cd", NULL), 1, ft_outc);
	g_sign = 1;
	ft_enable_raw(&sel);
	ft_init_select(&sel, av, *index);
	ft_get_size_term(&verif, &sel, 2);
	ft_test(&sel, ret);
	tputs(tgetstr("cd", NULL), 1, ft_outc);
	if (sel->ret)
		*line = ft_strdup(sel->ret);
	return (ft_disable_raw(0, &sel));
}
