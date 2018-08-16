/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:12:14 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:13 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

static void		ft_print_itoa(int n, size_t len, int fd)
{
	char		str[len + 1];
	size_t		i;
	long int	nb;

	i = -1;
	str[len + 1] = '\0';
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
	ft_putstr_fd(str, fd);
}

void			ft_putnbr_fd(int nb, int fd)
{
	size_t len;

	len = nb < 0 ? ft_nbrlen(nb * -1) : ft_nbrlen(nb);
	if (nb >= 2147483647)
		ft_putstr_fd("2147483647", fd);
	else if (nb <= -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
		nb < 0 ? ft_print_itoa(nb, len + 1, fd) : ft_print_itoa(nb, len, fd);
}
