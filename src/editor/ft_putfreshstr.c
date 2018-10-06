/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putfreshstr.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 03:50:17 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 20:53:47 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_putfreshstr(char *str)
{
	if (str)
	{
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		write(1, str, ft_strlen(str));
	}
}
