/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 09:03:20 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/stdin.h"
#include "../../include/builtins.h"

void	add_last_param(char **cmd)
{
	if (cmd)
		add_to_set("_", cmd[ft_tablen(cmd) - 1]);
}

int		ft_solver(t_op *t_exec, int fd, pid_t pid, int pipe)
{
	//	ft_get_bin();
	char *tmp_bin;
	char *raccmd;
	int ok;
	int flag;

	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
	{
		if (ft_builtins(t_exec, ok, flag) == EXIT_SUCCESS)
		{
			add_last_param(t_exec->cmd);
			return (EXIT_SUCCESS);
		}
		else
		{
			add_last_param(t_exec->cmd);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		raccmd = ft_strdup(t_exec->cmd[0]);
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		if (tmp_bin != NULL)
		{
			if (pipe == 0)
			{
				pid = fork();
			}
			if (ft_exec(t_exec, tmp_bin, fd, pid) == EXIT_SUCCESS)
			{
				ft_hashtable(tmp_bin, raccmd);
				ft_strdel(&raccmd);
				add_last_param(t_exec->cmd);
				return (EXIT_SUCCESS);
			}
			else
			{
				ft_strdel(&raccmd);
				add_last_param(t_exec->cmd);
				return (EXIT_FAILURE);
			}
		}
		else
			ft_print_error(t_exec->cmd[0], "command not found");
	}
	add_last_param(t_exec->cmd);
	return (EXIT_FAILURE);
}
