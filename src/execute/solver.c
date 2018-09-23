/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/23 20:48:03 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	add_pid_bin(int pid)
{
	char *tmp;

	if ((tmp = ft_itoa(pid)))
	{
		add_to_set("PID_BIN", tmp);
		ft_strdel(&tmp);
	}
}

static void	add_last_param(char **cmd)
{
	if (cmd)
		add_to_set("_", cmd[ft_tablen(cmd) - 1]);
}

int			waitstat2(int *status)
{
	wait(status);
	while (wait(NULL) > 0)
		;
	return (*status);
}

int ft_waiting2(int status)
{
	int ret;

	status = waitstat2(&status);
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int			ft_solver(t_op *t_exec, pid_t pid, t_loop *loop)
{
	char *raccmd;
	int status;
	int result;

	result = 0;
	if (ft_check_command(t_exec->cmd[0]) != 0)
	{
		add_last_param(t_exec->cmd);
		exit(result = ft_builtins(t_exec));
	}
	else
	{
		raccmd = ft_strdup(t_exec->cmd[0]);
		add_pid_bin(pid);
		execve(loop->bin, t_exec->cmd, g_env);
	}
	/*{
	  ft_hashtable(tmp_bin, raccmd);
	  ft_strdel(&raccmd);
	  add_last_param(t_exec->cmd);
	  ft_unset_var("PID_BIN");
	  }*/
	/*else
	  {
	  ft_strdel(&raccmd);
	  add_last_param(t_exec->cmd);
	  if (tmp_bin == NULL)
	  ft_print_error(t_exec->cmd[0], "Command not found !");*/
	//result = ft_waiting2(status);
	add_last_param(t_exec->cmd);
	return (result);
}
