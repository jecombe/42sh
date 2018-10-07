/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exit.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:34:28 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 08:22:21 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	ft_exit_error(char *cmd, t_bierror error, int ret)
{
	ft_putstr_fd("101sh: exit: ", STDERR_FILENO);
	if (error == BINUM)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (ret);
}

int			ft_exit(t_op *opera)
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	ft_putendl_fd("exit", 2);
	if (opera->cmd[1])
	{
		while (opera->cmd[1][++i])
			if (!(ft_isdigit(opera->cmd[1][i])))
				return (ft_exit_error(opera->cmd[1], BINUM, 255));
		if (opera->cmd[2])
			return (ft_exit_error(NULL, BITOMANY, 255));
		ret = ft_atoi(opera->cmd[1]);
		while (ret > 255)
			ret -= 256;
	}
	return (ret);
}
