/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/25 10:59:49 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/29 04:48:50 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

void	ft_error(const char *s, t_select **t)
{
	if (s[0])
	{
		ft_putstr_fd("ERROR :", 2);
		ft_putstr_fd(s, 2);
		ft_putchar_fd(2, '\n');
	}
	exit(ft_disable_raw(1, &(*t)));
}
