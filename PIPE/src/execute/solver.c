/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 02:27:28 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 04:38:40 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 02:26:20 by dzonda      ###    #+. /#+    ###.fr     */
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

void			ft_close(int save, int *fd, int input, int output)
{
	pid_t pid;

	if (g_input > 0)
		close(g_input);
	if (g_output!= 1)
		close(g_output);
	close(g_fd[1]);
	if (g_save)
		close(g_save);
	g_save = g_fd[0];
	g_c = 1;
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

int			ft_solver(t_op *t_exec, int fd, pid_t pid, int save, int *fdd, int input, int output)
{
	char *tmp_bin;
	char *raccmd;
	int ok;
	int status;
	int result;

	result = 0;
	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
		result = ft_builtins(t_exec, ok, 0, fd);
	else
	{
		raccmd = ft_strdup(t_exec->cmd[0]);
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		if (pid == 0)
		{
			add_pid_bin(pid);
			ft_exec2(t_exec, tmp_bin, fd, pid);
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
		}
		result = ft_waiting2(status);
	}
	add_last_param(t_exec->cmd);
	return (result);
}
