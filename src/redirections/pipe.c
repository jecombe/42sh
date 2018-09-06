/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 18:23:12 by jecombe     ###    #+. /#+    ###.fr     */
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


/*int 	ft_children_fork(t_op *op, int *fd, int fd_out, int i, int fd2)
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
  int flag;
  int ok  = 0;
  return ((ret = ft_builtins(op, ok, flag, fd2)));
  }
  else
  {
  return ((ret = ft_solver(op, -88, pid, 1)));
  printf("EXEC2\n");
//return (execve(bin, op->cmd, g_env));
}
exit(1);
//return (0);
}*/

int			waitstat(int *status, int buil)
{
	int ret;
	if (buil == 0)
		wait(status);
	while (wait(NULL) > 0)
		;
	return (*status);
}

int g_hh;
int g_ret;
int		ft_pipe_execute(int i, t_op *op, pid_t pidd, int *fd_pipe, int fd2)
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
	int u = i;

	while (i != 0)
	{
		g_last = 0;
		pipe(fd);
		t_op *op2;
		pid_t piddd;
		int fd_open;
		if (op->redirect && i - 1 != 0)
			if ((fd_open = ft_loop_redirect(op->redirect, 1, -1, 1)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		fd_out =  1;
		fd_in = 0;
		status = 0;
		if (ft_check_command(op->cmd[0]) != 0)
		{
			g_hh = 10;
		}
		else
			g_hh = 0;
		bin = ft_search_bin(op->cmd[0]);
		if (bin == NULL)
			return (EXIT_FAILURE);
		if ((fork()) == 0 && bin != NULL)
		{
			dup2(fd_in != 0 ? fd_in : fd_save, STDIN_FILENO);
			if (i != 1 && fd_out == 1)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			pid_t pid;
			if (ft_check_command(op->cmd[0]) != 0)
			{
				int flag;
				g_ret = ft_builtins(op, ok, flag, fd2);
				exit(1);
			}
			else
			{
				if (i - 1 == 0)
					g_last = 1;
				return ((ret = ft_solver(op, -88, pid, 1)));
			}
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
	if (g_hh == 10)
	{
		return (g_ret);
	}
	ret = WEXITSTATUS(status);
	if (bin == NULL)
		return (EXIT_FAILURE);
	if (ret > 0)
	{
		g_hh = 0;
		return (EXIT_FAILURE);
	}
	else
	{
		g_hh =  0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}




int		ft_pipe(t_op *opera, int i, pid_t pid, int fd2)
{
	int ret;
	int fdd[3];

	ret = ft_pipe_execute(i, opera, pid, fdd, fd2);
	return (ret);
}
