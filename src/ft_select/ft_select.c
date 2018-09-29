/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:46:16 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_select(t_editor **ed, int version)
{
	if ((*ed)->t.elem)
	{
		version == 0 ? ft_init_select(ed) : 0;
		if ((*ed)->sel->bp < (*ed)->sel->ws.ws_col)
		{
			if ((*ed)->t.elem[1])
			{
//				printf("0000\n");
//				sleep(2);
				version == 0 ? ft_print_params((*ed)->sel) : 0;
				(*ed)->tabu = 0;
			}
			else if ((*ed)->t.elem[0] && (*ed)->tabu == -1)
			{
//				printf("1111\n");
//				sleep(2);
					replace_line_after_tab(ed);
					//REPLACE LINE AFTER TAB
			}
			version == 1 ? ft_manage_touch(ed) : 0;
		}
		else
		{
//				printf("22222\n");
//				sleep(2);
			return (1);
		}
//		sleep(2);
	}
	return (0);
}
