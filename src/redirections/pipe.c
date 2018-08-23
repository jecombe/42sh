/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/23 17:55:59 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		ft_count_pipe(t_op *tmp)
{
	t_op *tmpp = tmp;
	int i =  0;
	while (tmpp->token == PIPE)
	{
		i++;
		tmpp = tmpp->next;
	}
	return (i);
}

int 	ft_children_fork(t_op *op, int *fd, int fd_out, int i)
{	
	char *bin;
	int ret;

	bin = ft_search_bin(op->cmd[0]);
	if (i != 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	pid_t pid;
	//execve(bin, op->cmd, g_env);
	//return (0);
	return ((ret = ft_solver(op, -88, pid, 1)));
}

int			waitstat(int *status)
{
	int ret;
	wait(status);
	while (wait(NULL) > 0)
		;
	ret = WEXITSTATUS(status);
	return (*status);
}

int		ft_pipe_execute(int i, t_op *op, pid_t pidd, int *fd_pipe)
{
	int fd[2];
	int status = 0;
	int fd_save =0;
	int fd_out = 1;
	int fd_in = 0;
	int stat;
	int ret;

	while (i != 0)
	{
		pipe(fd);
		fd_out =  1;
		fd_in = 0;
		status = 0;
		if ((fork()) == 0)
		{
			dup2(fd_save, STDIN_FILENO);
			ft_children_fork(op, fd, fd_out, i);
		}
		else
		{	
			if (fd_in > 0)
				close(fd_in);
			if (fd_out != 1)
				close(fd_out);
			close(fd[1]);
			if (fd_save)
				close(fd_save);
			fd_save = fd[0];
			op = op->next;
			i--;
		}
	}
	status = waitstat(&status);
	ret = WEXITSTATUS(status);
	if (ret == 1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}


int		ft_pipe(t_op *opera, int i, pid_t pid)
{
	int ret;
	int fdd[3];

	ret = ft_pipe_execute(i, opera, pid, fdd);
	return (ret);
}
