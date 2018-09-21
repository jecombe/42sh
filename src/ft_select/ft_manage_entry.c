/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_entry.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:29:05 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 23:12:49 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

int		ft_manage_entry(t_editor **ed, t_select **sel)
{
	int		ret;

	ret = 1;
	ret = ft_manage_touch((*ed)->key, &(*sel), &(*ed)->tabu);
	return (ret);
}
