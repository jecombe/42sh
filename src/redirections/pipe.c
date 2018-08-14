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

int		ft_pipe_execute(int i, t_op *op, pid_t pid)
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
}

int		ft_pipe(t_op *opera, int i, pid_t pid)
{
	int ret;

	ret = ft_pipe_execute(i + 1, opera, pid);
	return (ret);
}
