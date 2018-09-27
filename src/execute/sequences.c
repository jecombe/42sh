/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sequences.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:01:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 17:23:22 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void			ft_save_fd(int fd_org[3])
{
	fd_org[0] = dup(0);
	fd_org[1] = dup(1);
	fd_org[2] = dup(2);
}

static void			ft_restore_fd(int fd_org[3])
{
	dup2(fd_org[0], 0);
	dup2(fd_org[1], 1);
	dup2(fd_org[2], 2);
}

static void			ft_loop_reset(t_loop *loop)
{
	loop->fd_in = 0;
	loop->fd_out = 1;
}

int					ft_pipe(t_op *opera, int fd2)
{
	t_loop			loop;
	int				pfd[2];
	int				fd[3];
	int				result;

	ft_memset(&loop, 0, sizeof(t_loop));
	ft_memset(&pfd, 0, sizeof(int) * 2);
	ft_memset(&fd, 0, sizeof(int) * 3);
	ft_save_fd(fd);
	while (opera)
	{
		pipe(pfd);
		ft_loop_reset(&loop);
		if (ft_loop_redirect(opera->redirect, fd2, pfd[1], &loop) == EXIT_FAILURE)
			return(EXIT_FAILURE);
		result = ft_exec(opera, &loop, pfd);
		if (opera->token != PIPE)
			break ;
		opera = opera->next;
	}
	ft_restore_fd(fd);
	return (ft_return_command(&loop, result));
}

void		ft_sequence(t_seq *b_seq, int fd)
{
	t_seq *seq;
	t_token	tkn;
	int		ret;

	seq = NULL;
	tkn = TOKEN;
	ret = EXIT_SUCCESS;
	seq = b_seq;
	while (seq && seq->op)
	{
		if ((tkn == TOKEN) || (tkn == AND_IF && !ret) || (tkn == OR_IF && ret))
			ret = ft_pipe(seq->op, fd);
		tkn = seq->op->token;
		printf("%d \n", seq->op->token);
		if ((seq->op = seq->op->next) == NULL)
			seq = seq->next;
	}
}
