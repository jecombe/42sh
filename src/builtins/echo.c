/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:34:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 06:12:45 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int 		ft_echo(t_op *t_exec, int flag)
{
	//printf("ECHO\n");
	int flag2;
	int fd_open;
	int i;
	int slash_n;
	int ok = 0;

	//printf("=========+> %s\n", t_exec->cmd[1]);
	if (t_exec->cmd[1] == NULL)
	{
		ok = 1;
		t_exec->cmd[1] = "\0";
	}
	slash_n = 0;
	i = 1;
	if (ft_strcmp(t_exec->cmd[1], "-n") == 0)
	{
		slash_n = 1;
		i++;
		//printf("======>--%s--\n", t_exec->cmd[i]);
	}
	if (flag != -1)
	{
		if (flag == O_RDONLY)
			flag2 = O_RDONLY;
		else
			flag2 = O_WRONLY;
			while (t_exec->cmd[i])
			{
				if (flag2 == O_WRONLY)
				{
					fd_open = open(t_exec->redirect->file, flag2 | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
					ft_putstr_fd(t_exec->cmd[i], fd_open);
					if (t_exec->cmd[i + 1])
						ft_putchar_fd(' ', fd_open);
				}
				if (flag2 == O_RDONLY)
					fd_open = open(t_exec->redirect->file, flag2);
				i++;
			}
		if (slash_n == 0)
			ft_putchar_fd('\n', fd_open);
		else
			ft_putchar_fd('\0', fd_open);
	}
	else
	{
		if (ok == 1)
			ft_putchar('\n');
	else
		{
			while (t_exec->cmd[i])
			{
				ft_putstr(t_exec->cmd[i]);
				if (t_exec->cmd[i + 1])
					ft_putchar(' ');
				i++;
			}
		}
	}
	return (0);
}
