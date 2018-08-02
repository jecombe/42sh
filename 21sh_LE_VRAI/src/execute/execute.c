/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:52:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:31:26 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int				ft_exec(t_op *tmp_op, char **env, char *bin_cmd)
{
	pid_t		cpid;
	int			status;
	int			ret;
	char		*cmd;

	ret = 0;
	if ((cpid = fork()) == 0)
	{
		if (execve(bin_cmd, tmp_op->cmd, env) == -1)
		{
			printf("JFGIGFEIBZBF\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("kHSHSHSHSHSHSHSHS\n");
			exit(EXIT_SUCCESS);
		}
	}
	if (cpid > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	if (ret == 1)
	{
		printf("ok1\nn");
		return (2);
	}
	else

	{
		printf("ok2\n");
		return (0);
	}
}


