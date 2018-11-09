/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 05:17:27 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 17:09:29 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void			add_pid_bin(int pid)
{
	char *tmp;

	if ((tmp = ft_itoa(pid)))
	{
		add_to_set("PID_BIN", tmp);
		ft_strdel(&tmp);
	}
}

static void			ft_close_fd(t_loop *loop, int pfd[2])
{
	(loop->fd_in > 0) ? close(loop->fd_in) : 0;
	(loop->fd_out != 1) ? close(loop->fd_out) : 0;
	(loop->fd_save) ? close(loop->fd_save) : 0;
	close(pfd[1]);
	loop->fd_save = pfd[0];
}

void				ft_solve(t_op *opera, t_loop *loop, pid_t *pid, int pfd[2])
{
	if ((*pid = vfork()) == 0)
	{
		dup2(loop->fd_in != 0 ? loop->fd_in : loop->fd_save, STDIN_FILENO);
		if (opera->token == PIPE && loop->fd_out == 1)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		if (loop->bin == NULL)
		{
			ft_print_error(opera->cmd[0], "Command not found !");
			ft_putstr("\007");
			loop->result = -1;
			exit(EXIT_FAILURE);
		}
		if (isbuiltin(loop->bin, 1) == EXIT_SUCCESS)
		{
			loop->ok = 1;
			exit(ft_builtins(opera, loop));
		}
		if (isbuiltin(opera->cmd[0], 2) == EXIT_SUCCESS)
			exit(loop->result);
		else
		{
			add_pid_bin(*pid);
			ft_hashtable(loop->bin, opera->cmd[0]);
			execve(loop->bin, opera->cmd, g_env);
			exit(0);
		}
	}
	else
		ft_close_fd(loop, pfd);
}
