/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_color.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 14:28:43 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/23 18:58:53 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

static void		ft_bold(int nb, int fd)
{
	if (nb == 8)
		ft_putstr_fd(BLACKB, fd);
	if (nb == 9)
		ft_putstr_fd(REDB, fd);
	if (nb == 10)
		ft_putstr_fd(GREENB, fd);
	if (nb == 11)
		ft_putstr_fd(YELLOWB, fd);
	if (nb == 12)
		ft_putstr_fd(BLUEB, fd);
	if (nb == 13)
		ft_putstr_fd(PURPLEB, fd);
	if (nb == 14)
		ft_putstr_fd(CYANB, fd);
	if (nb == 15)
		ft_putstr_fd(GREYB, fd);
}

void			ft_putstr_color(char const *s, int nb, int fd)
{
	if (s)
	{
		if (nb == 0)
			ft_putstr_fd(BLACK, fd);
		if (nb == 1)
			ft_putstr_fd(RED, fd);
		if (nb == 2)
			ft_putstr_fd(GREEN, fd);
		if (nb == 3)
			ft_putstr_fd(YELLOW, fd);
		if (nb == 4)
			ft_putstr_fd(BLUE, fd);
		if (nb == 5)
			ft_putstr_fd(PURPLE, fd);
		if (nb == 6)
			ft_putstr_fd(CYAN, fd);
		if (nb == 7)
			ft_putstr_fd(GREY, fd);
		else
			ft_bold(nb, fd);
		ft_putstr_fd(s, fd);
	}
}
