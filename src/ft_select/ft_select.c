/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/23 02:45:22 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

static int	ft_manage_raw(t_term *raw, int version)
{
	/*	if (version == 0)
		{
		if (tcgetattr(STDIN_FILENO, raw) == -1)
		return (1);
		(*raw).c_cc[VMIN] = 1;
		(*raw).c_cc[VTIME] = 0;
		if (tcsetattr(STDIN_FILENO, TCSANOW, raw) == -1)
		return (1);
		tputs(tgetstr("vi", NULL), 1, ft_outc);
		}
		else
		{
		(*raw).c_cc[VMIN] = 0;
		(*raw).c_cc[VTIME] = 1;
		if (tcsetattr(STDIN_FILENO, TCSANOW, raw) == -1)
		return (1);
		tputs(tgetstr("ve", NULL), 1, ft_outc);
		}*/
	return (0);
}

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
	//	tputs(tgetstr("cd", NULL), 1, ft_outc);
	//	while ((*sel && ret != 4) || ret == 0)
	//	{
	//	refresh = ft_refresh((*sel), ret);
	//		if (refresh == 1)
	//		{
	//		printf("REFRESH == %d\n", refresh);
	//		sleep(2);
	//			ft_print_params(*sel);
	//		}
	//		refresh == 2 ? ft_putstr_fd("\E[0J", 2) : 0;
	ret = ft_manage_entry(ed, &(*sel));
	//	}
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
	ft_manage_raw(&raw, 1);
	return (0);
}
