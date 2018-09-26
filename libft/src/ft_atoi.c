/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:08:57 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:33:46 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int				ft_atoi(const char *nptr)
{
	int			i;
	int			nb;
	char		neg;

	i = 0;
	nb = 0;
	neg = '\0';
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		neg = nptr[i];
	i += neg ? 1 : 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + (nptr[i++] - '0');
	return (neg == '-' ? nb * (-1) : nb);
}
