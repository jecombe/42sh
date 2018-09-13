/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 16:11:24 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"
int		ft_count_pipe(t_op *tmp)
{
	t_op *tmpp = tmp;
	int i;

	i = 0;
	while (tmpp->token == PIPE)
	{
		i++;
		tmpp = tmpp->next;
	}
	return (i);
}

int	ft_children_fork(t_pipe **tpipe, int *fd, t_op *op, int fd2, int ret)
{
	int fd_open;

	dup2((*tpipe)->fd_in != 0 ? (*tpipe)->fd_in : (*tpipe)->fd_save, STDIN_FILENO);
	if ((*tpipe)->start != 1 && (*tpipe)->fd_out == 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	pid_t pid;
	if ((*tpipe)->buil_pipe == 0)
		if (ft_loop_redirect(op->redirect, 0, -88, 0) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	execve((*tpipe)->bin, op->cmd, g_env);
	return (0);
}

void			ft_parent_fork(t_pipe **tpipe, t_op *op, int *fd)
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

int			waitstat(int *status, t_pipe **tpipe)
{
	if ((*tpipe)->built == 0)
		wait(status);
	while (wait(NULL) > 0)
		;
	return (*status);
}

int ft_waiting(int status, t_pipe **tpipe)
{
	int ret;

	status = waitstat(&status, tpipe);
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
void		ft_exec_fork_pipe(t_pipe **tpipe, int *fd, t_op *o, int fd2, int ret)
{
	if (fork() == 0)
	{
		if ((*tpipe)->buil_pipe == 10)
		{
			if (o->redirect)
				close(STDOUT_FILENO);
			close(STDERR_FILENO);
		}
		ret = ft_children_fork(tpipe, fd, o, fd2, ret);
	}
	else
		ft_parent_fork(tpipe, o, fd);
}

int		ft_exec_no_null(t_op *op, int fd2, t_pipe *tpipe, int *fd)
{
	int fd_open;
	int ret;

	if ((tpipe->built = ft_check_command(op->cmd[0]) != 0))
	{
		tpipe->buil_pipe = 10;
		tpipe->ret = ft_builtins(op, 101, 0, fd2);
	}
	else
	{
		tpipe->buil_pipe = 0;
		if (op->redirect && tpipe->start - 1 != 0)
			if ((fd_open = ft_loop_redirect(op->redirect, 1, -1, 1)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	ft_exec_fork_pipe(&tpipe, fd, op, fd2, ret);
	return (0);
}

int			ft_return_pipe(int status, t_pipe *tpipe)
{
	int finish;

	if ((finish = ft_waiting(status, &tpipe)) == EXIT_SUCCESS)
	{
		if (tpipe->bin == NULL)
			return (EXIT_FAILURE);
		if (tpipe->built != 0)
			return (tpipe->ret);
		return (EXIT_SUCCESS);
	}
	if (finish == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}

int		ft_pipe(t_op *op, int co, int fd2)
{
	int fd[2];
	int status;
	t_pipe tpipe;
	int fd_open;

	status = 0;
	tpipe = ft_init_pipe(co);
	while (tpipe.start != 0)
	{
		pipe(fd);
		tpipe.fd_out =  1;
		tpipe.fd_in = 0;
		status = 0;
		tpipe.bin = ft_search_bin(op->cmd[0]);
		if (tpipe.bin != NULL)
			ft_exec_no_null(op, fd2, &tpipe, fd);
		else
			ft_print_error(op->cmd[0], "Command not found !");
		op = op->next;
		tpipe.start--;
	}
	return (ft_return_pipe(status, &tpipe));
}
