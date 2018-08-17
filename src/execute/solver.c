/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 06:31:46 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/stdin.h"



int		ft_solver(t_op *t_exec, int fd, pid_t pid)
{
//	ft_get_bin();
	char *tmp_bin;
	char *raccmd;
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
		raccmd = ft_strdup(t_exec->cmd[0]);
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		ft_putendl(tmp_bin);
		if (t_exec->token != PIPE)
			pid = fork();
		if (ft_exec(t_exec, tmp_bin, fd, pid) == EXIT_SUCCESS)
		{
			ft_hashtable(tmp_bin, raccmd);
			ft_strdel(&raccmd);
			return (EXIT_SUCCESS);
		}
		else
		{
			ft_strdel(&raccmd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_FAILURE);
}
