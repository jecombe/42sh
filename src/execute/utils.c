/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:25:35 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 17:10:35 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void			ft_print_error(const char *s1, const char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

void			ft_print_message(char *source, int nb)
{
	if (nb == -1)
		ft_print_error(source, "is a directory");
	else if (nb == -2)
		ft_print_error(source, "permission denied !");
	else if (nb == -3)
		ft_print_error(source, "no such file or directory");
}
