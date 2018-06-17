/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:32:15 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/17 19:07:00 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	nb;
	int		neg;

	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	neg = (str[i] == '-') ? -1 : 1;
	i = (str[i] == '+' || str[i] == '-') ? i + 1 : i;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i++] - '0');
		if (i > 20)
			return (neg == -1 ? 0 : -1);
	}
	return (nb * neg);
}
