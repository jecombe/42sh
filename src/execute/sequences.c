/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sequences.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:01:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 17:02:26 by jecombe     ###    #+. /#+    ###.fr     */
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
	loop->result = -1;
	while (opera)
	{
		pipe(pfd);
		ft_loop_reset(loop);
		if (ft_loop_redirect(opera->redirect, fd2, pfd[1], loop) > 0)
		{
			ft_restore_fd(fd);
			add_to_set("?", "1");
			return (EXIT_FAILURE);
		}
		ft_exec(opera, loop, pfd);
		if (opera->token != PIPE || loop->exit == 1)
			break ;
		opera->next ? free(loop->bin) : 0;
		opera->token == PIPE ? ft_restore_fd(fd) : 0;
		opera = opera->next;
	}
	ft_restore_fd(fd);
	return (ft_return_command(loop));
}

int				ft_sequence(t_seq *b_seq, int fd)
{
	t_seq		*seq;
	t_token		tk;
	int			ret;
	t_op		*op;
	t_loop		loop;

	seq = NULL;
	tk = TOKEN;
	ret = EXIT_SUCCESS;
	seq = b_seq;
	while (seq)
	{
		op = seq->op;
		while (op)
		{
			if (tk == TOKEN || (tk == AND_IF && !ret) || (tk == OR_IF && ret))
				ret = ft_pipe(op, fd, &loop);
			if (loop.exit == 1)
				return (loop.result);
			tk = op->token;
			op = op->next;
		}
		seq = seq->next;
	}
	return (999);
}
