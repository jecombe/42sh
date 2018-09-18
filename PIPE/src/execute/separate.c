/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   separate.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:00:53 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 04:51:52 by dzonda      ###    #+. /#+    ###.fr     */
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


static void			ft_parent_fork(t_pipe **tpipe, t_op *op)
{
	if ((*tpipe)->fd_in > 0)
		close((*tpipe)->fd_in);
	if ((*tpipe)->fd_out != 1)
		close((*tpipe)->fd_out);
	close(g_fd[1]);
	if ((*tpipe)->fd_save)
		close((*tpipe)->fd_save);
	(*tpipe)->fd_save = g_fd[0];
}

int		ft_loop_redirect2(t_redirect *redirect,  int fd2, int  ouput, int save, int input, int *fdd, t_loop *loop)
{
	int file;
	int flag;

	flag = 0;
	file = -1;
	while (redirect)
	{
		if (redirect->redirect == DLESS)
			loop->fd_in = ft_redirect_heredoc(redirect, 0);
		if (redirect->redirect == GREAT || redirect->redirect == DGREAT)
		{
			flag = ft_return_flag(redirect);
			loop->fd_out = ft_open_redirect(redirect->file ,flag, O_WRONLY);
		}
		if (redirect->redirect == LESS)
		{
			if (ft_check_source(redirect->file) == -1)
			{
				ft_print_message(redirect->file, 2);
				return (EXIT_FAILURE);
			}
			loop->fd_in = ft_open_redirect(redirect->file, O_RDONLY, 0);
		}
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}

t_loop		*init_loop(void)
{
	t_loop	*loop;

	if (!(loop = malloc(sizeof(t_loop))))
		return (NULL);
	loop->fd_in = 0;
	loop->fd_out = 1;
	loop->fd_save = 0;
	return (loop);
}

int			ft_go_pipe(t_op *opera)
{
	int i = ft_count_pipe(opera);
	int status = 0;
	t_loop *loop;

	i++;
	pid_t pid;
	loop = init_loop();
	while (i != 0)
	{
		pipe(g_fd);
		//g_input = 0;
		//g_output =1;
		loop->fd_in = 0;
		loop->fd_out = 1;
		if (ft_loop_redirect2(opera->redirect, 0, 0, 0, 0, 0, loop) == EXIT_FAILURE)
			return(EXIT_FAILURE);
		if ((pid = fork()) == 0)
		{
			dup2(loop->fd_in != 0 ? loop->fd_in : loop->fd_save, STDIN_FILENO);
			if (i != 1 && loop->fd_out == 1)
				dup2(g_fd[1], (opera->redirect) ? opera->redirect->fd : STDOUT_FILENO);
			if (loop->fd_out != 1)
				dup2(loop->fd_out, (opera->redirect) ? opera->redirect->fd : STDOUT_FILENO);
			close(g_fd[0]);
			ft_solver(opera, 0, pid, 0, 0, 0, 1);
			exit(-1);
		}
		else
		{
			if (loop->fd_in  > 0)
				close(loop->fd_in);
			if (loop->fd_out!= 1)
				close(loop->fd_out);
			close(g_fd[1]);
			if (loop->fd_save)
				close(loop->fd_save);
			loop->fd_save = g_fd[0];
			i--;
			opera = opera->next;
		}
	}
	free(loop);
	wait(&status);
	while(wait(NULL) > 0)
		;
	status = WEXITSTATUS(status);
	return(WEXITSTATUS(status));

}

void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
{
	t_op	*opera;
	int		fd_org[3];

	opera = b_seq->op;
	while (opera)
	{
		ft_save_fd(fd_org);
		ft_go_pipe(opera);
		ft_restore_fd(fd_org);
		return ;
		opera = opera->next;
	}
	return ;
}
