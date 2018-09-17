/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 04:59:58 by jecombe     ###    #+. /#+    ###.fr     */
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
	int flag;
	int fd_dup[3];
	int po[2];
	int status;
	int result;
	//g_save  = 0;
	//int save;

	if (ft_loop_redirect2(t_exec->redirect, fd, output, save, input, fdd) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	//dup2((*tpipe)->fd_in != 0 ? (*tpipe)->fd_in : (*tpipe)->fd_save, STDIN_FILENO);

	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
	{
		if (ft_builtins(t_exec, ok, flag, fd) == EXIT_SUCCESS)
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
		//g_output =  1;
		//g_input = 0;
		if ((pid = fork()) == 0)
		{
		add_pid_bin(pid);
		dup2(g_input != 0 ? g_input : g_save, STDIN_FILENO);
		if (g_start != 1 && g_output == 1)
			dup2(g_fd[1], STDOUT_FILENO);
		if (g_output != 1)
		{

		}
		close(g_fd[0]);
//		dup2((*tpipe)->fd_in != 0 ? (*tpipe)->fd_in : (*tpipe)->fd_save, STDIN_FILENO);
//	if ((*tpipe)->start != 1 && (*tpipe)->fd_out == 1)
//		dup2(g_fd[1], STDOUT_FILENO);
//	close(g_fd[0]);
printf("FORKING pour : %s\n",t_exec->cmd[0]);

		ft_exec2(t_exec, tmp_bin, fd, pid);
		/*{
			ft_hashtable(tmp_bin, raccmd);
			ft_strdel(&raccmd);
			add_last_param(t_exec->cmd);
			ft_unset_var("PID_BIN");
			//return (EXIT_SUCCESS);
		}
		else
		{
			ft_strdel(&raccmd);
			add_last_param(t_exec->cmd);
			if (tmp_bin == NULL)
				ft_print_error(t_exec->cmd[0], "Command not found !");*/

		//	return (EXIT_FAILURE);
		//}
	}
		else
			ft_close(save,fdd,input, output);
	}
	result = ft_waiting2(status);
	/*	dup2(STDIN_FILENO, fd_org[0]);
		dup2(STDOUT_FILENO, fd_org[1]);
		dup2(STDERR_FILENO, fd_org[2]);
		
		tant que exec
			tant que yq des pipe
				tqnt que solver
		*/

	add_last_param(t_exec->cmd);
	return (result);
}
