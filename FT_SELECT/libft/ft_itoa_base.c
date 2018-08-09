/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 18:46:19 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 18:19:28 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_itoa_base(int n, int base)
{
	int		i;
	long	nb;
	char	*res;

	nb = n < 0 ? -(long)n : (long)n;
	i = n <= 0 && base == 10 ? 1 : 0;
	i = n == 0 && base != 10 ? 1 : i;
	while (nb > 0 && ++i)
		nb /= base;
	if (!(res = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	res[i--] = '\0';
	nb = n < 0 ? -(long)n : (long)n;
	while (i >= 0)
	{
		res[i--] = (nb % base) >= 10 ? (nb % base) + 55 : (nb % base) + 48;
		nb /= base;
	}
	res[0] = n < 0 && base == 10 ? '-' : res[0];
	return (res);
}
