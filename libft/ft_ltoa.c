/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ltoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 09:04:21 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 19:34:34 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long value)
{
	long	i;
	long	base;
	long	nb;
	char	*res;

	base = 10;
	nb = value < 0 ? -value : value;
	i = value == 0 || (value < 0 && base == 10) ? 1 : 0;
	while (nb > 0)
	{
		nb /= base;
		i++;
	}
	if (!(res = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	res[i--] = '\0';
	nb = value < 0 ? -value : value;
	while (i >= 0)
	{
		res[i] = (nb % base) >= 10 ? (nb % base) + 65 - 10 : (nb % base) + 48;
		nb /= base;
		i--;
	}
	res[0] = value < 0 && base == 10 ? '-' : res[0];
	return (res);
}
