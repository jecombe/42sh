/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 06:50:50 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 18:39:47 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		set(t_op *exec, int p, int fd)
{
	int		i;
	int fd_open;

	i = 0;
	fd_open = ft_prelim_loop(exec, fd, 1);
	if (exec->redirect == NULL && p == 1)
			fd_open = 5;
	if (!exec->cmd[1])
		while (g_set[i])
			ft_putendl_fd(g_set[i++], fd_open);
	return (0);
}
