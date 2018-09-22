/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   separate.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:00:53 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 18:38:07 by jecombe     ###    #+. /#+    ###.fr     */
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


int		ft_loop_redirect(t_redirect *redirect,  int fd2, int fd_one, t_loop *loop)
{
	int file;
	int flag;

	flag = 0;
	file = -1;
	if (fd2 > 1)
	{

		loop->fd_out = ft_open_redirect(".tmp_file", O_TRUNC, O_WRONLY);
		dup2(loop->fd_out, 1);
	}
	while (redirect)
	{
		if (redirect->redirect == DLESS)
			loop->fd_in = ft_redirect_heredoc(redirect, 0);
		if (redirect->redirect == GREAT || redirect->redirect == DGREAT)
		{
			if (ft_check_file_is_directory(redirect->file) == -1)
			{
				ft_print_message(redirect->file, 1);
				return (EXIT_FAILURE);
			}
			flag = ft_return_flag(redirect);
			loop->fd_out = ft_open_redirect(redirect->file ,flag, O_WRONLY);
			dup2(loop->fd_out, redirect->fd);
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
		if (redirect->redirect == GREATAND || redirect->redirect == LESSAND)
		{
			if (ft_strcmp("-", redirect->file) == 0)
			{
				close(redirect->fd);
			}
			if (ft_strcmp("1", redirect->file) == 0)
				dup2(1, STDERR_FILENO);
			if (ft_strcmp("2", redirect->file) == 0)
				dup2(STDERR_FILENO, fd_one);
		}
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}

int			ft_waitstat(int *status, int builtins)
{
	if (g_builtins == 0)
		wait(status);
	while(wait(NULL) > 0)
		;
	return (*status);
}
int			ft_waiting(int status, int builtins)
{
	int ret;

	status = ft_waitstat(&status, builtins);
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}
int			ft_return_command(int status, char *bin, int builtins)
{
	int finish;

	if ((finish = ft_waiting(status, builtins)) == EXIT_SUCCESS)
	{
		if (bin == NULL)
		{
			printf("FAILURE\n");
			return (EXIT_FAILURE);
		}
		printf("SUCCES\n");
		return (EXIT_SUCCESS);
	}
	printf("FAILURE\n");
	return (EXIT_FAILURE);
}
int			ft_go_pipe(t_op *opera, int fd2)
{
	int i = ft_count_pipe(opera);
	int status = 0;
	t_loop loop;
	int fd[2];
	char *tmp_bin;
	int builtins;
	int ok;

	i++;
	pid_t pid;
	loop = ft_init_loop();
	while (i != 0)
	{
		pipe(fd);
		loop.fd_in = 0;
		loop.fd_out = 1;
		if (ft_loop_redirect(opera->redirect, fd2, fd[1], &loop) == EXIT_FAILURE)
			return(EXIT_FAILURE);
			tmp_bin = ft_search_bin(opera->cmd[0]);
			// verififer que la commande n'est pas exit, et peut etre d'autres commandes x. Faut executer la commande x ici, et pas dans solver.
			if (ft_strcmp("exit", opera->cmd[0]) == 0)
				ft_exit(opera);
		if (tmp_bin != NULL)
		{
			if ((pid = fork()) == 0)
			{
				dup2(loop.fd_in != 0 ? loop.fd_in : loop.fd_save, STDIN_FILENO);
				if (i != 1 && loop.fd_out == 1)
					dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				ft_solver(opera, pid, tmp_bin);
				//exit(-1);
			}
			else
			{
				if (loop.fd_in  > 0)
					close(loop.fd_in);
				if (loop.fd_out!= 1)
					close(loop.fd_out);
				close(fd[1]);
				if (loop.fd_save)
					close(loop.fd_save);
				loop.fd_save = fd[0];
				i--;
				opera = opera->next;
			}
		}
		else
		{
			ft_print_error(opera->cmd[0], "Command not found !");
			opera = opera->next;
			i--;
		}
	}
	return (ft_return_command(status, tmp_bin, builtins));
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
