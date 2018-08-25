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
		ft_putstr(BLACKB);
	if (nb == 9)
		ft_putstr(REDB);
	if (nb == 10)
		ft_putstr(GREENB);
	if (nb == 11)
		ft_putstr(YELLOWB);
	if (nb == 12)
		ft_putstr(BLUEB);
	if (nb == 13)
		ft_putstr(PURPLEB);
	if (nb == 14)
		ft_putstr(CYANB);
	if (nb == 15)
		ft_putstr(GREYB);
}

void			ft_putstr_color(char const *s, int nb)
{
	if (s)
	{
		if (nb == 0)
			ft_putstr(BLACK);
		if (nb == 1)
			ft_putstr(REDD);
		if (nb == 2)
			ft_putstr(GREEN);
		if (nb == 3)
			ft_putstr(YELLOW);
		if (nb == 4)
			ft_putstr(BLUEE);
		if (nb == 5)
			ft_putstr(PURPLE);
		if (nb == 6)
			ft_putstr(CYAN);
		if (nb == 7)
			ft_putstr(GREY);
		else
			ft_bold(nb);
		ft_putstr(s);
	}
}
