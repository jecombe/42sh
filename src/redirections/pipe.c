/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/11 15:03:08 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 15:22:28 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 15:03:05 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"
int g_hh;
int g_ret;
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

int	ft_children_fork(t_pipe **tpipe, int *fd, t_op *op, int fd2, int ret, char *bin, int co)
{
	int flag;
	int fd_open;
	int ok = 0;
	dup2((*tpipe)->fd_in != 0 ? (*tpipe)->fd_in : (*tpipe)->fd_save, STDIN_FILENO);
	if (co != 1 && (*tpipe)->fd_out == 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	pid_t pid;
	if ((*tpipe)->buil_pipe == 0)
		if (ft_loop_redirect(op->redirect, 0, -88, 0) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	execve(bin, op->cmd, g_env);
	return (0);
}



void			ft_parent_fork(t_pipe **tpipe, t_op *op, int *fd, char *bin)
{
	if ((*tpipe)->fd_in > 0)
		close((*tpipe)->fd_in);
	if ((*tpipe)->fd_out != 1)
		close((*tpipe)->fd_out);
	close(fd[1]);
	if ((*tpipe)->fd_save)
		close((*tpipe)->fd_save);
	(*tpipe)->fd_save = fd[0];
}

int			waitstat(int *status)
{
	int ret;
	if (g_hh == 0)
		wait(status);
	while (wait(NULL) > 0)
		;
	return (*status);
}

int ft_waiting(int status, int ret, char *bin, t_pipe *tpipe)
{
	status = waitstat(&status);
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_exec_no_null(t_op *op, int fd2, t_pipe *tpipe, int *fd, char *bin, int co)
{
	int fd_open;
	int ret;

	if ((g_hh = ft_check_command(op->cmd[0]) != 0))
	{
		tpipe->buil_pipe = 10;
		g_ret = ft_builtins(op, 101, 0, fd2);
	}
	else
	{
		tpipe->buil_pipe = 0;
		if (op->redirect && co - 1 != 0)
			if ((fd_open = ft_loop_redirect(op->redirect, 1, -1, 1)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	if (fork() == 0)
	{
		if (tpipe->buil_pipe == 10)
		{
			if (op->redirect)
				close(STDOUT_FILENO);
			close(STDERR_FILENO);
		}
		ret = ft_children_fork(&tpipe, fd, op, fd2, ret, bin, co);
	}
	else
		ft_parent_fork(&tpipe, op, fd, bin);
	//tpipe->buil_pipe = 0;
	return (0);
}

int		ft_pipe_execute(int co, t_op *op, pid_t pidd, int fd2)
{
	int fd[2];
	int status = 0;
	int ret;
	char *bin;
	t_pipe tpipe;
	int fd_open;
	int finish;
	int flag;
	int ok;

	tpipe = ft_init_pipe(co);
	while (co != 0)
	{
		pipe(fd);
		tpipe.fd_out =  1;
		tpipe.fd_in = 0;
		status = 0;
		bin = ft_search_bin(op->cmd[0]);
		if (bin != NULL)
			ft_exec_no_null(op, fd2, &tpipe, fd, bin, co);
		else
			ft_print_error(op->cmd[0], "Command not found !");
		op = op->next;
		co--;
	}
	tpipe.buil_pipe = 0;
	if ((finish = ft_waiting(status, ret, bin, &tpipe)) == EXIT_SUCCESS)
	{
		if (bin == NULL)
			return (EXIT_FAILURE);
		if (g_hh != 0)
			return (g_ret);
		return (EXIT_SUCCESS);
	}
	if (finish == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}

int		ft_pipe(t_op *opera, int i, pid_t pid, int fd2)
{
	int ret;
	int fdd[3];

	ret = ft_pipe_execute(i, opera, pid, fd2);
	return (ret);
}
/*
int	ft_children_fork(t_pipe *tpipe, int *fd, t_op *op, int fd2, int i, int ret, char *bin)
{
	int flag;
	int fd_open;
	//pid_t pid;
	int ok = 0;
	dup2(tpipe->fd_in != 0 ? tpipe->fd_in : tpipe->fd_save, STDIN_FILENO);
	if (i != 1 && tpipe->fd_out == 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	pid_t pid;
	if (g_last == 0)
	{
		if (ft_loop_redirect(op->redirect, 0, -88, 0) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	execve(bin, op->cmd, g_env);
	return (0);
}



void			ft_parent_fork(t_pipe *tpipe, t_op *op, int *fd, char *bin)
{
	if ((*tpipe).fd_in > 0)
		close((*tpipe).fd_in);
	if ((*tpipe).fd_out != 1)
		close((*tpipe).fd_out);
	close(fd[1]);
	if ((*tpipe).fd_save)
		close((*tpipe).fd_save);
	(*tpipe).fd_save = fd[0];
}

int			waitstat(int *status)
{
	int ret;
	if (g_hh == 0)
		wait(status);
	while (wait(NULL) > 0)
		;
	return (*status);
}

int ft_waiting(int status, int ret, char *bin, int i, t_pipe *tpipe)
{
	status = waitstat(&status);
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_pipe_execute(int i, t_op *op, pid_t pidd, int fd2)
{
	int fd[2];
	int status = 0;
	int ret;
	char *bin;
	t_pipe tpipe;
	int fd_open;
	int finish;
	int flag;
	int ok;

	tpipe = ft_init_pipe(i);
	while (i != 0)
	{
		pipe(fd);
		tpipe.fd_out =  1;
		tpipe.fd_in = 0;
		status = 0;
		bin = ft_search_bin(op->cmd[0]);
		if (bin != NULL)
		{
			if ((g_hh = ft_check_command(op->cmd[0]) != 0))
			{

				g_last = 10;
				g_ret = ft_builtins(op, 101, flag, fd2);
			}
			else
			{
				g_last = 0;
				if (op->redirect && i - 1 != 0)
					if ((fd_open = ft_loop_redirect(op->redirect, 1, -1, 1)) == EXIT_FAILURE)
						return (EXIT_FAILURE);
			}
			if (fork() == 0)
			{
				if (g_last == 10)
				{
					if (op->redirect)
						close(STDOUT_FILENO);
					close(STDERR_FILENO);
				}
				ret = ft_children_fork(&tpipe, fd, op, fd2, i, ret, bin);
			}
			else
			{
				ft_parent_fork(&tpipe, op, fd, bin);
				op = op->next;
				i--;
			}
		}
		else
		{
			ft_print_error(op->cmd[0], "Command not found !");
			op = op->next;
			i--;
		}
	}
	if ((finish = ft_waiting(status, ret, bin, i, &tpipe)) == EXIT_SUCCESS)
	{
		if (bin == NULL)
			return (EXIT_FAILURE);
		if (g_hh != 0)
			return (g_ret);
		return (EXIT_SUCCESS);
	}
	if (finish == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}
int		ft_pipe(t_op *opera, int i, pid_t pid, int fd2)
{
	int ret;
	int fdd[3];

	ret = ft_pipe_execute(i, opera, pid, fd2);
	g_last = 0;
	return (ret);
}*/
