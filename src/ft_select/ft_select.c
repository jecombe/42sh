/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 14:05:09 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

static int		ft_refresh(t_select *t, int ret)
{
	if (ret == 0)
		return (t->bp > t->ws.ws_col ? 2 : 1);
	return (0);
}

int				ft_test(t_select **sel, int ret)
{
	char		*entry;
	int			refresh;

	refresh = 0;
	entry = NULL;
	ft_get_size_term(&(*sel)->ws, &(*sel), 2);
	while ((*sel && ret != 4) || ret == 0)
	{
		refresh = ft_refresh((*sel), ret);
		if (refresh == 1)
		{
			ft_print_params(&(*sel));
		}
		refresh == 2 ? ft_putstr_fd("\E[0J", 2) : 0;
		ret = ft_manage_entry(&entry, &(*sel));
		entry ? ft_strdel(&entry) : 0;
	}
	return (0);
}

int			ft_select(char **av, char **line, int *index, int version)
{
	t_select	*sel;
	int			ret;

	ret = 0;
	tputs(tgetstr("cd", NULL), 1, ft_outc);
//	ft_enable_raw(&sel);
//	printf("SELECT\n");
//	sleep(2);
	ft_init_select(&sel, av, *index);
	ft_get_size_term(&sel->ws, &sel, 2);
	ft_test(&sel, ret);
	tputs(tgetstr("cd", NULL), 1, ft_outc);
	if (sel->ret)
		*line = ft_strdup(sel->ret);
	return (ft_free_t_select(&sel));
}
