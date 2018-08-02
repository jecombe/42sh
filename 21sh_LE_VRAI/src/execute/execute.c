/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:52:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 15:40:17 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int				ft_exec(t_op *tmp_op, char **env, char *bin_cmd, int flag)
{
	pid_t		cpid;
	int			status;
	int			ret;
	char		*cmd;
	int ret2;
	int			flag2;

	if (flag == O_RDONLY)
		flag2 = O_RDONLY;
	else
		flag2 = O_WRONLY;
	ret = 0;
	if ((cpid = fork()) == 0)
	{
		if (flag != -1)
			ft_open_redirect(tmp_op->redirect->file, flag, flag2);
		if (execve(bin_cmd, tmp_op->cmd, env) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
		//if (flag != -1)
			close (ret2);
	}
	if (cpid > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	if (ret == 1)
	{
		printf("ok1\n");
		return (2);
	}
	else

	{
		printf("ok2\n");
		return (0);
	}
}


