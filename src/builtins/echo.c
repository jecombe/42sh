/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:34:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 17:09:43 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int 		ft_echo_redirect(int fd_open, char **cmd, int ok, int slash_n)
{
	int i = 0;

	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd_open);
		if (cmd[i + 1])
			ft_putchar_fd(' ', fd_open);
		i++;
	}
	if (slash_n == 0 && ok == 0)
		ft_putchar_fd('\n', fd_open);
	return (EXIT_SUCCESS);

}

int 		ft_echo_normal(t_op *t_exec, int i, int ok, int slash_n)
{	
	if (ok == 1)
	{
		ft_putchar('\n');
		return (EXIT_SUCCESS);
	}
	while (t_exec->cmd[i])
	{
		ft_putstr(t_exec->cmd[i]);
		if (t_exec->cmd[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (slash_n == 0)
		ft_putchar('\n');
	return (EXIT_SUCCESS);

}
int 		ft_echo(t_op *t_exec, int flag)
{
	//printf("ECHO\n");
	int flag2;
	int fd_open;
	int i;
	int slash_n;
	int ok = 0;

	if (t_exec->cmd[1] == NULL)
	{
		ok = 1;
		t_exec->cmd[1] = "\n";
		t_exec->cmd[2] = NULL;
	}
	slash_n = 0;
	i = 1;
	if (ft_strcmp(t_exec->cmd[1], "-n") == 0)
	{
		slash_n = 1;
		i++;
	}
	if (flag != NOTHING)
	{

		if ((fd_open = ft_open_redirect_builtins(t_exec->redirect->file, flag)) != -11)
			ft_echo_redirect(fd_open, t_exec->cmd + i, ok, slash_n);
	}
	else
		ft_echo_normal(t_exec, i, ok, slash_n);
	return (EXIT_SUCCESS);
}
