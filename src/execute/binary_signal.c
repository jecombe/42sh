/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary_signal.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 17:33:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 11:29:56 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		binary_signal(int status, int pid, char *bin)
{
	char	*tmp;

	if ((status >= 6 && status <= 8) || (status >= 10 && status <= 16))
	{
		ft_putstr_fd("[1]\t", 2);
		tmp = ft_itoa(pid);
		ft_putstr_fd(tmp, 2);
		write(2, " ", 1);
		ft_strdel(&tmp);
	}
	status == 6 ? ft_putstr_fd("ABORT", 2) : 0;
	status == 7 ? ft_putstr_fd("BUS ERROR", 2) : 0;
	status == 8 ? ft_putstr_fd("FLOATING-POINT EXEPTION", 2) : 0;
	status == 11 ? ft_putstr_fd("SEGMENTATION FAULT", 2) : 0;
	status == 13 ? ft_putstr_fd("BROKEN PIPE", 2) : 0;
	status == 16 ? ft_putstr_fd("STACK FAULT", 2) : 0;
	if ((status >= 6 && status <= 8) || (status >= 10 && status <= 16))
	{
		write(2, "\t", 1);
		ft_putendl_fd(bin, 2);
	}
	return (0);
}
