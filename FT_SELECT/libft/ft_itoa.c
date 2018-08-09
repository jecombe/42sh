/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 00:29:50 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 00:29:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str_return;
	int		i;
	int		div;
	int		neg;

	if ((div = 1) && n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = n < 0 ? 1 : 0;
	neg = n < 0 ? -1 : 1;
	n *= n < 0 ? -1 : 1;
	while ((n / div) != 0 && ++i)
		div *= 10;
	n == 0 ? i = 1 : 0;
	i > 9 ? i = 10 : 0;
	div = 1;
	i = n >= 1000000000 && neg == -1 ? 11 : i;
	if (!(str_return = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	str_return[i] = '\0';
	while (--i >= 0 ? 1 : 0)
	{
		i != 0 || neg == 1 ? str_return[i] = (n / div) % 10 + '0' : (div *= 10);
		!(i != 0 || neg == 1) ? str_return[0] = '-' : (div *= 10);
	}
	return (str_return);
}
