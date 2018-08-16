/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/15 22:56:52 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		ft_count_pipe(t_op *tmp)
{
	t_op *tmpp = tmp;
	while (tmpp->token == PIPE)
	{
		g_i++;
		tmpp = tmpp->next;
	}
	return (g_i);
}

void	ft_ex(t_op *op)
{
	int		status;
	int		pid;
	int		err;
	char	**env;
	int ret;
	int		fd[2];
	static int nice = 0;

	char *bin;
	ft_get_bin();
	printf("OK1 -%s-\n", op->cmd[0]);
	bin = ft_search_bin(op->cmd[0]);
	printf("OK1 %s\n", op->cmd[0]);

	if (g_i == 2)
	{
		printf("OK1 %s\n", op->cmd[0]);
		pipe(fd);
	}

	printf("OK2 %s\n", op->cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		//signal(SIGINT, SIG_DFL);
		/*if (g_i == 2)
		  {*/

		printf("OK3 %s\n", op->cmd[0]);
		dup2(fd[1],1);
		close(fd[0]);
		//}
		dup2(nice, 0);
		err = execve(bin, op->cmd, g_env);
	}
	else if (pid < 0)
	{
		ft_putstr("fork failed with error code ");
		ft_putnbr(pid);
		ft_putchar('\n');
	}
	printf("OK4 %s\n", op->cmd[0]);
	wait(&status);
	close(fd[1]);
	nice = fd[0];

}
void		fils_pute(t_op *op, int fd[2])
{	char *bin;
	ft_get_bin();
	printf("OK1 -%s-\n", op->cmd[0]);
	bin = ft_search_bin(op->cmd[0]);
	printf("OK1 %s\n", op->cmd[0]);
	;

	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execve(bin, op->cmd, g_env);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
}


int		ft_pipe_execute(int i, t_op *op, pid_t pidd, int *fd_pipe)
{
	t_op *tmp;
	int fd[2];
	int fdd[7];
	pid_t pid;
	int ret = 0;
	//pid_t pid;
	if (op->next == NULL)
	{	char *bin;
		ft_get_bin();
		bin = ft_search_bin(op->cmd[0]);
		printf("OKNULL %s\n", op->cmd[0]);
		return (execve(bin, op->cmd, g_env));
	}
	if (!op)
		return (0);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		fils_pute(op, fd);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		return (ft_pipe_execute(i, op->next, pidd,fdd));
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (0);
}

int		ft_pipe(t_op *opera, int i, pid_t pid, int *fd_pipe)
{
	int ret;

	ret = ft_pipe_execute(g_i, opera, pid, fd_pipe);
	return (EXIT_SUCCESS);
}
