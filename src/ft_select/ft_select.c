/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 16:35:42 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_select(t_editor **ed, int version)
{
	int			ret;
	t_term		raw;

	ret = 0;
	if ((*ed)->t.elem)
	{
		version == 0 ? ft_init_select(ed) : 0;
		if ((*ed)->sel->bp < (*ed)->sel->ws.ws_col)
		{
			if ((*ed)->t.elem[1])
			{
				version == 0 ? ft_print_params((*ed)->sel) : 0;
				(*ed)->tabu = 0;
			}
			else if ((*ed)->t.elem[0] && (*ed)->tabu == -1)
			{
				if ((*ed)->t.elem[0])
				{
					replace_line_after_tab(ed);
					//REPLACE LINE AFTER TAB
				}
			}
			version == 1 ? ft_manage_touch(ed) : 0;
		}
	}
	return (0);
}
