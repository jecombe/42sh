/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 11:40:03 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_select(t_editor **ed, char **line, int version)
{
	int			ret;
	t_term		raw;

	ret = 0;
///	printf("ENTER INSIDE FT_SELECT\n");
///	sleep(1);
	version == 0 ? ft_init_select(ed) : 0;
///	printf("3111\n");
///	sleep(1);
	version == 0 ? ft_print_params((*ed)->sel) : 0;
///	printf("3222\n");
///	sleep(1);
	version == 1 ? ft_manage_touch(ed) : 0;
///	printf("3033\n");
///	sleep(1);
	return (0);
}
