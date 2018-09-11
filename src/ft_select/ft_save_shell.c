/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_save_shell.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/29 08:17:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:10:05 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_save_shell(t_select **t, int version)
{
	static t_select *save;

	if (version == 0)
		save = *t;
	else if (version == 1)
		*t = save;
}
