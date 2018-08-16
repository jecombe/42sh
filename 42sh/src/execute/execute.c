/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:52:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/15 21:53:46 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int				ft_exec(t_op *tmp_op, char *bin_cmd, int fd, pid_t pid, int *fd_pipe)
{
	//pid_t		cpid;
	int			status;
	int			ret;
	t_redirect *redirect;
	int fd_pip[2];
	static int fdd = 0;
	int ok = 0;

	redirect = NULL;
	ret = 0;
	if (tmp_op->redirect)
	{
		redirect = tmp_op->redirect;
	}
	//pid = fork();
	/*if (tmp_op->next)
	{
		ok = 1;
		printf("OK1 %s %s\n", tmp_op->cmd[0], tmp_op->next->cmd[0]);
		pipe(fd_pip);
	}
		printf("OK2 %s\n", tmp_op->cmd[0]);
	pid = fork();*/
		//Gestion des multiples redirections
	/*if (pid == 0)
	{
		//Gestion des multiples redirections
			if (ft_loop_redirect(redirect, bin_cmd, pid, 0, tmp_op->cmd, tmp_op, fd) == EXIT_SUCCESS)
		else
			return(EXIT_FAILURE);*/
		//EXECVE
		if (execve(bin_cmd, tmp_op->cmd, g_env) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	//}
	/*if (pid > 0)
	{
		printf("OK4 %s\n", tmp_op->cmd[0]);
		wait(0);
		ret = WEXITSTATUS(status);
		//close(fd_pip[1]);
		//fdd = fd_pip[0];
	}
	if (ret == 1)
	{
		//ECHEC
		return (EXIT_FAILURE);
	}
	else
	{
		//REUSSITE
		return (EXIT_SUCCESS);
	}*/
}
