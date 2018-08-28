/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 19:21:44 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int g_ok;

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

	if (i != 1 && fd_out == 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	pid_t pid;
	bin = ft_search_bin(op->cmd[0]);
	if (bin == NULL)
		return (EXIT_FAILURE);
	if (ft_check_command(op->cmd[0]) != 0)
	{
		g_ok = 1;
		int flag;
		return ((ret = ft_builtins(op, g_ok, flag)));
	}
	else
	{
		g_ok = 0;
		//return ((ret = ft_solver(op, -88, pid, 1)));
		printf("EXEC2\n");
	return (execve(bin, op->cmd, g_env));
	}
	exit(1);
	//return (0);
}

int			waitstat(int *status, int buil)
{
	int ret;
	if (buil == 0)
		wait(status);
	while (wait(NULL) > 0)
		;
	//ret = WEXITSTATUS(status);
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
	char *bin;
	int ok = 0;

	printf("IIIIIII %d\n", i);
	while (i != 0)
	{
	printf("IIIIIII %d\n", i);
		pipe(fd);
		fd_out =  1;
		fd_in = 0;
		printf("-----------------> %s %d %d\n", op->cmd[0], fd_in, fd_out);
		status = 0;
		bin = ft_search_bin(op->cmd[0]);
		/*if (bin == NULL)
			break;*/
		/*if (ft_check_command(op->cmd[0]) != 0)
		{
			g_ok = 1;
			int flag;
			//ft_builtins(op, ok, flag);
		}
		else
			g_ok = 0;*/
		if ((fork()) == 0)
		{
			dup2(fd_in != 0 ? fd_in : fd_save, STDIN_FILENO);
			//char *bin;
			//int ret;

			if (i != 1 && fd_out == 1)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			pid_t pid;
			//bin = ft_search_bin(op->cmd[0]);
			if (ft_check_command(op->cmd[0]) != 0)
			{
				g_ok = 1;
				int flag;
				printf("OOOOOOOOOOOOOOK\n");
				ret = ft_builtins(op, ok, flag);
				exit(1);
			}
			else
			{
				g_ok = 0;
				printf("EXEC\n");
				execve(bin, op->cmd, g_env);
				//return ((ret = ft_solver(op, -88, pid, 1)));
			}
			//ft_children_fork(op, fd, fd_out, i);
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
	status = waitstat(&status, ok);
	ret = WEXITSTATUS(status);
	if (ret > 0)
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
