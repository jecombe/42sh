/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   manage_loop_fd.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/30 17:46:47 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 14:11:44 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_save_fd(int fd_org[3])
{
	fd_org[0] = dup(0);
	fd_org[1] = dup(1);
	fd_org[2] = dup(2);
}

void		ft_restore_fd(int fd_org[3])
{
	dup2(fd_org[0], 0);
	dup2(fd_org[1], 1);
	dup2(fd_org[2], 2);
}

void		ft_loop_reset(t_loop *loop)
{
	loop->fd_in = 0;
	loop->fd_out = 1;
}
