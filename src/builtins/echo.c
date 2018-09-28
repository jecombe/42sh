/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:34:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 04:24:39 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_echo(t_op *opera)
{
	int i;

	i = 0;
	if (opera->cmd[1] == NULL)
		ft_putchar_fd('\n', 1);
	else
	{
		if (ft_strcmp(opera->cmd[1], "-n") == 0)
			i++;
		while (opera->cmd[++i])
		{
			ft_putstr_fd(opera->cmd[i], 1);
			if (opera->cmd[i + 1])
				ft_putchar_fd(' ', 1);
		}
		if (opera->cmd[1] != NULL && ft_strcmp(opera->cmd[1], "-n") != 0)
			ft_putchar_fd('\n', 1);
	}
	return (EXIT_SUCCESS);
}
