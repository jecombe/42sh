/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/15 21:39:19 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/stdin.h"

int		ft_solver(t_op *t_exec, int fd, pid_t pid, int *fd_pipe)
{
	ft_get_bin();
	char *tmp_bin;
	int ok;
	int flag;


	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
	{
		if (ft_builtins(t_exec, ok, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	else
	{
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		/*if (t_exec->next && t_exec->token == PIPE)
		{
			printf("OK NEXT %s %s\n", t_exec->cmd[0], t_exec->next->cmd[0]);
			pipe(fd_pipe);
		}*/
		//pid = fork();
		//if (pid == 0)
		//{
		if (ft_exec(t_exec, tmp_bin, fd, pid, fd_pipe) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
		//}
		//else
			//wait(0);
	}
	return (EXIT_FAILURE);
}
