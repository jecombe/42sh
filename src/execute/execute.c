/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:52:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 04:33:41 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int				ft_exec(t_op *tmp_op, char *bin_cmd, int flag, int fd)
{
	pid_t		cpid;
	int			status;
	int			ret;
	char		*cmd;
	int			flag2;

	if (fd != -12)
	{
		if (flag == O_RDONLY)
			flag2 = O_RDONLY;
		else
			flag2 = O_WRONLY;
	}
	ret = 0;
	if ((cpid = fork()) == 0)
	{
		if (fd != -12)
			if (flag != -1)
				ft_open_redirect(tmp_op->redirect->file, flag, flag2, fd);
		if (execve(bin_cmd, tmp_op->cmd, g_env) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	if (cpid > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	if (ret == 1)
	{
		//ECHEC
		return (2);
	}
	else
	{
		//REUSSITE
		return (0);
	}
}


