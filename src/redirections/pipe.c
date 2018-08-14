/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:54:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 14:56:43 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		ft_count_pipe(t_op *tmp)
{
	int i =  0;
	while (tmp->token == PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		ft_pipe_execute(int i, t_op *op)
{
	t_op *tmp;
	int fd[2];
	int ret = 0;
	int fdd = 0;
	pid_t pid;

	fdd = 0;
	tmp = op;
	ret = 0;
	while (i != 0)
	{
		ret = ft_solver(tmp, i);
		tmp = tmp->next;
		i--;
	}
	return (ret);
}

int		ft_pipe(t_op *opera, int i)
{
	int ret;

	ret = ft_pipe_execute(i + 1, opera);
	return (ret);
}
