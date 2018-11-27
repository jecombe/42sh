/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:12:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 08:08:11 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

static void		ft_print_itoa(int n, size_t len)
{
	char		str[len + 1];
	size_t		i;
	long int	nb;

	i = -1;
	ft_bzero(str, sizeof(str));
	while (str[++i])
		str[i] = '\0';
	nb = (long int)n;
	i = n < 0 ? (ft_nbrlen(n) + 1) : ft_nbrlen(n);
	nb *= n < 0 ? -1 : 1;
	while (nb != 0 && i != 0)
	{
		str[--i] = '0' + (nb % 10);
		nb /= 10;
	}
	n < 0 ? str[0] = '-' : 0;
	n == 0 ? str[0] = '0' : 0;
	ft_putstr(str);
}

void			ft_putnbr(int nb)
{
	size_t len;

	len = 0;
	len = nb < 0 ? ft_nbrlen(nb * -1) : ft_nbrlen(nb);
	if (nb >= 2147483647)
		ft_putstr("2147483647");
	else if (nb <= -2147483648)
		ft_putstr("-2147483648");
	else
		nb < 0 ? ft_print_itoa(nb, len + 1) : ft_print_itoa(nb, len);
}
