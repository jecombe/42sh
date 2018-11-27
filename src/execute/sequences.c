/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sequences.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:01:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 11:52:08 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				ft_pipe(t_op *opera, int fd2, t_loop *loop)
{
	int			pfd[2];
	int			fd[3];

	ft_memset(loop, 0, sizeof(t_loop));
	ft_save_fd(fd);
	while (opera)
	{
		loop->result = -1;
		opera->token == PIPE ? pipe(pfd) : 0;
		ft_loop_reset(loop);
		if (ft_loop_redirect(opera->redirect, fd2, pfd[1], loop) < 1)
			ft_exec(opera, loop, pfd, fd2);
		if (loop->exit == 1 || opera->token != PIPE)
			break ;
		opera->next ? ft_strdel(&loop->bin) : 0;
		opera->token == PIPE ? ft_restore_fd(fd) : 0;
		opera = opera->next;
	}
	ft_restore_fd(fd);
	return (ft_return_command(loop));
}

int				ft_sequence(t_seq *b_seq, int fd, t_loop *loop)
{
	t_seq		*seq;
	int			ret;
	t_op		*op;

	seq = NULL;
	ret = EXIT_SUCCESS;
	seq = b_seq;
	op = seq->op;
	ret = ft_pipe(op, fd, loop);
	return (ret);
}
