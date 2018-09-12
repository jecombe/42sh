/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prelim_loop.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/12 17:06:22 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 17:17:40 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"
int			ft_prelim_loop(t_op *exec, int fd, int std_err)
{
	int fd_open;
	if (fd > 2)
	{
		if ((fd_open = ft_loop_redirect(exec->redirect, 1, fd, 0)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		fd = 1;
		if ((fd_open = ft_loop_redirect(exec->redirect, 1, fd, 0)) == EXIT_FAILURE)
		{
			printf("FAIL\n");
			return(EXIT_FAILURE);
		}
		if (fd_open < 1)
			fd_open = 2;
		if (exec->redirect)
		{
			if (std_err == 0)
			{
			if (exec->redirect->fd == 1)
				fd_open = 2;
			}
			else
			{
				if (exec->redirect->fd > 1)
					fd_open = exec->redirect->fd;
			}
		}
		printf("=====> %d\n", fd_open);
	}
	return (fd_open);
}
