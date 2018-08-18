/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 16:01:12 by jecombe     ###    #+. /#+    ###.fr     */
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

/*int		ft_pipe_execute(int i, t_op *op, pid_t pid)
  {
  t_op *tmp;
  int fd[2];
  int ret = 0;
  int fdd = 0;
//pid_t pid;

tmp = op;
ret = 0;
while (i != 0)
{
pipe(fd);
pid = fork();
if (pid == 0)
{	dup2(fdd, 0);
if (i - 1 != 0)
dup2(fd[1], 1);
close(fd[0]);
ret = ft_solver(tmp, -3, pid);
}
if (pid > 0)
{
wait(0);
close(fd[1]);
fdd = dup(fd[0]);
}
i--;
tmp = tmp->next;
}
return (ret);
}*/


void		fils_pute(t_op *op, int *fd, int fd_out)
{	char *bin;
	//ft_get_bin();
	bin = ft_search_bin(op->cmd[0]);
	if (op->next)
	{
		dup2(fd[1], STDOUT_FILENO);
	}
	close(fd[0]);
	execve(bin, op->cmd, g_env);
}

int			waitstat(int *status)
{
	wait(status);
	while (wait(NULL) > 0)
		;
	return (*status);
}
int		ft_pipe_execute(int i, t_op *op, pid_t pidd, int *fd_pipe)
{
	int fd[2];
	int status = 0;
	int fd_save =0;
	int fd_out = 1;
	int fd_in = 0;

	while (op)
	{
		pipe(fd);
		fd_out =  1;
		fd_in = 0;
		status = 0;

		if ((fork()) == 0)
		{
			dup2(fd_save, STDIN_FILENO);
			fils_pute(op, fd, fd_out);
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
		}

	}
	status = waitstat(&status);
	WEXITSTATUS(status);
	return (0);
}


int		ft_pipe(t_op *opera, int i, pid_t pid)
{
	int ret;
	int fdd[3];

	ret = ft_pipe_execute(i + 1, opera, pid, fdd);
	return (ret);
}
