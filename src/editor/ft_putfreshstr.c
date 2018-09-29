/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putfreshstr.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 03:50:17 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 17:42:35 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_putfreshstr(char *str)
{
	int		i;

	i = -1;
	if (str)
		while (str[++i])
		{
			tputs(tgetstr("ce", NULL), 1, ft_putchar);
			write(1, &str[i], 1);
		}
}
