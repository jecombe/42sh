/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	add_pid_bin(int pid)
{
	char *tmp;

	if ((tmp = ft_itoa(pid)))
	{
		add_to_set("PID_BIN", tmp);
		ft_strdel(&tmp);
	}
}

static void	add_last_param(char **cmd)
{
	if (cmd)
		add_to_set("_", cmd[ft_tablen(cmd) - 1]);
}

static void ft_close_fd(t_loop *loop, int pfd[2])
{
	(loop->fd_in  > 0) ? close(loop->fd_in) : 0;
	(loop->fd_out!= 1) ? close(loop->fd_out) : 0;
	(loop->fd_save) ? close(loop->fd_save) : 0;
	close(pfd[1]);
	loop->fd_save = pfd[0];
}

void		ft_solve(t_op *opera, t_loop *loop, pid_t *pid, int pfd[2])
{
	if ((*pid = fork()) == 0)
	{
		dup2(loop->fd_in != 0 ? loop->fd_in : loop->fd_save, STDIN_FILENO);
		if (opera->token == PIPE && loop->fd_out == 1)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		if (isbuiltin(loop->bin, 1) == EXIT_SUCCESS)
			exit (ft_builtins(opera));
		else
		{
			execve(loop->bin, opera->cmd, g_env);
			exit (EXIT_FAILURE);
		}
	}
	else
		ft_close_fd(loop, pfd);
}

void		ft_exec(t_op *opera, t_loop *loop, int *pfd)
{
	pid_t	pid;

	pid = -1;
	if (!opera->cmd)
	{
		loop->result = EXIT_SUCCESS;
		return ;
	}
	if (isbuiltin(opera->cmd[0], 0) == EXIT_SUCCESS)
	{
		loop->bin = "isbuiltin";
		loop->result = ft_builtins(opera);
	}
	else if ((loop->bin = ft_search_bin(opera->cmd[0])))
	{
		ft_solve(opera, loop, &pid, pfd);
		add_last_param(opera->cmd);
		ft_hashtable(loop->bin, opera->cmd[0]);
		add_pid_bin(pid);
	}
	else
		ft_print_error(opera->cmd[0], "Command not found !");
}
