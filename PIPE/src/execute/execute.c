/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:52:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 02:28:48 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"
/*int			waitstat(int *status)
{
	wait(status);
	while (wait(NULL) > 0)
		;
	return (*status);
}

int ft_waiting(int status, t_pipe **tpipe)
{
	int ret;

	status = waitstat(&status);
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}*/
int				ft_exec(t_op *tmp_op, char *bin_cmd, int fd, pid_t pid)
{
	//pid_t		cpid;
	int			status;
	int			ret;
	t_redirect *redirect;

	redirect = NULL;
	ret = 0;
	if (tmp_op->redirect)
		redirect = tmp_op->redirect;
		//Gestion des multiples redirections
	if (pid == 0 || fd == -88)
	{
		//Gestion des multiples redirections
		//	if (ft_loop_redirect(redirect, 0, fd, 0) == EXIT_FAILURE)
		//	return(EXIT_FAILURE);
		//execve
			if (execve(bin_cmd, tmp_op->cmd, g_env) == -1)
				exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	if (pid > 0 && fd != -88)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
		binary_signal(status, pid, bin_cmd);
	}
	return (ret > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
void			ft_exec2(t_op *tmp_op, char *bin_cmd, int fd, pid_t pid)
{
	//pid_t		cpid;
	int			status;
	int			ret;
	t_redirect *redirect;

	execve(bin_cmd, tmp_op->cmd, g_env);
}
