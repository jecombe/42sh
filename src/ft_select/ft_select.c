/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 09:33:19 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

static int		ft_refresh(t_select *t, int ret)
{
	if (ret == 0)
		return (t->bp > t->ws.ws_col ? 2 : 1);
	return (0);
}

int				ft_test(t_select **sel, int ret, t_editor **ed)
{
	int			refresh;

	refresh = 0;
	ret = ft_manage_entry(ed, &(*sel));
	return (0);
}

int			ft_select(t_editor **ed, char **line, int version)
{
	int			ret;
	t_term		raw;

	ret = 0;
	version == 0 ? ft_init_select(&(*ed)->sel, (*ed)->t.elem, (*ed)->tabu) : 0;
	version == 0 ? ft_print_params((*ed)->sel) : 0;
	version == 1 ? ft_manage_entry(ed, &(*ed)->sel) : 0;
//	version == 1 ? ft_test(&(*ed)->sel, ret, ed) : 0;
	if ((*ed)->sel->ret)
		*line = ft_strdup((*ed)->sel->ret);

	return (0);
}
