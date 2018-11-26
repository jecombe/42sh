/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/16 22:57:09 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 17:20:54 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void				add_pid_bin(int pid)
{
	char	*tmp;

	if ((tmp = ft_itoa(pid)))
	{
		add_to_set("PID_BIN", tmp);
		ft_strdel(&tmp);
	}
}

static void			ft_close_fd(t_loop *loop, int pfd[2], t_op *opera)
{
	(loop->fd_in > 0) ? close(loop->fd_in) : 0;
	(loop->fd_out != 1) ? close(loop->fd_out) : 0;
	if (opera->token == PIPE)
	{
		(loop->fd_save) ? close(loop->fd_save) : 0;
		close(pfd[1]);
		loop->fd_save = pfd[0];
	}
}

static void			ft_execve(t_loop *loop, t_op *opera)
{
	add_pid_bin(loop->pid);
	execve(loop->bin, opera->cmd, g_env);
}

void				ft_solve(t_op *opera, t_loop *loop, int pfd[2])
{
	if ((loop->pid = fork()) == 0)
	{
		dup2(loop->fd_in != 0 ? loop->fd_in : loop->fd_save, STDIN_FILENO);
		if (opera->token == PIPE)
		{
			loop->fd_out == 1 ? dup2(pfd[1], 1) : 0;
			close(pfd[0]);
		}
		if (loop->bin == NULL)
			exit(ft_command_not_found(opera, loop));
		if (isbuiltin(opera->cmd[0]) == EXIT_SUCCESS && opera->token == PIPE)
			exit(ft_builtins(opera, loop));
		else
		{
			ft_execve(loop, opera);
			exit(EXIT_SUCCESS);
		}
	}
	else
		ft_close_fd(loop, pfd, opera);
}
