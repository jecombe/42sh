/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_color.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 14:28:43 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 15:37:19 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

static void		ft_bold(int nb)
{
	if (nb == 8)
		ft_putstr_fd(BLACKB, 2);
	if (nb == 9)
		ft_putstr_fd(REDB, 2);
	if (nb == 10)
		ft_putstr_fd(GREENB, 2);
	if (nb == 11)
		ft_putstr_fd(YELLOWB, 2);
	if (nb == 12)
		ft_putstr_fd(BLUEB, 2);
	if (nb == 13)
		ft_putstr_fd(PURPLEB, 2);
	if (nb == 14)
		ft_putstr_fd(CYANB, 2);
	if (nb == 15)
		ft_putstr_fd(GREYB, 2);
}

void			ft_putstr_color(char const *s, int nb)
{
	if (s)
	{
		if (nb == 0)
			ft_putstr_fd(BLACK, 2);
		if (nb == 1)
			ft_putstr_fd(REDD, 2);
		if (nb == 2)
			ft_putstr_fd(GREEN, 2);
		if (nb == 3)
			ft_putstr_fd(YELLOW, 2);
		if (nb == 4)
			ft_putstr_fd(BLUEE, 2);
		if (nb == 5)
			ft_putstr_fd(PURPLE, 2);
		if (nb == 6)
			ft_putstr_fd(CYAN, 2);
		if (nb == 7)
			ft_putstr_fd(GREY, 2);
		else
			ft_bold(nb);
		ft_putstr_fd(s, 2);
	}
}
