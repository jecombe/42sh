/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   separate.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:00:53 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 05:31:25 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	ft_save_fd(int fd_org[3])
{
	fd_org[0] = dup(0);
	fd_org[1] = dup(1);
	fd_org[2] = dup(2);
}

void	ft_restore_fd(int fd_org[3])
{
	dup2(fd_org[0], 0);
	dup2(fd_org[1], 1);
	dup2(fd_org[2], 2);
}


int			ft_waiting()
{
	int status;
	int ret;

	status = 0;
	wait(&status);
	while(wait(NULL) > 0)
		;
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int			ft_return_command(t_loop *loop)
{

	if (ft_waiting() == EXIT_SUCCESS)
	{
		if (loop->bin == NULL)
		{
			add_to_set("?", "1");
			return (EXIT_FAILURE);
		}
		add_to_set("?", "0");
		return (EXIT_SUCCESS);
	}
	add_to_set("?", "1");
	return (EXIT_FAILURE);
}

void			ft_exec_no_null(t_op *opera, t_loop *loop, int *fd)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		dup2(loop->fd_in != 0 ? loop->fd_in : loop->fd_save, STDIN_FILENO);
		if (loop->start != 1 && loop->fd_out == 1)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ft_solver(opera, pid, loop);
	}
	else
	{
		if (loop->fd_in  > 0)
			close(loop->fd_in);
		if (loop->fd_out!= 1)
			close(loop->fd_out);
		close(fd[1]);
		if (loop->fd_save)
			close(loop->fd_save);
		loop->fd_save = fd[0];
	}
}

int			ft_go_pipe(t_op *opera, int fd2)
{
	t_loop loop;
	int fd[2];
	char *tmp_bin;
	int i;

	i = ft_count_pipe(opera);
	i++;
	loop = ft_init_loop(i);
	while (loop.start != 0)
	{
		pipe(fd);
		loop.fd_in = 0;
		loop.fd_out = 1;
		if (ft_loop_redirect(opera->redirect, fd2, fd[1], &loop) == EXIT_FAILURE)
			return(EXIT_FAILURE);
		loop.bin = ft_check_command2(opera->cmd[0]);
		if (loop.bin != NULL)
			ft_exec_no_null(opera, &loop, fd);
		else
			ft_print_error(opera->cmd[0], "Command not found !");
		opera = opera->next;
		loop.start--;
	}
	return (ft_return_command(&loop));
}

void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
{
	t_op	*opera;
	int		fd_org[3];
	int ret;
	int		i;

	i = 0;
	opera = b_seq->op;
	t_token tk;
	ret = 0;
	while (opera)
	{
		tk = b_seq->op->token;
		ft_save_fd(fd_org);
		if ((tk == TOKEN) || (tk == AND_IF && !ret) || (tk == OR_IF && ret) || i == 0)
			ret = ft_go_pipe(opera, fd);
		ft_restore_fd(fd_org);
		opera = opera->next;
		i++;
	}
}
