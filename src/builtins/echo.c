/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:34:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 18:29:33 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

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

int 		ft_echo(t_op *t_exec, int flag, int fd, int p)
{
	int flag2;
	int fd_open;
	int i;
	int slash_n;

	int ok = 0;
	t_op *op = NULL;
	if (t_exec->cmd[1] == NULL)
	{
		ok = 1;
		ft_malloc_cmd(&t_exec->cmd, "\n");
	}
	slash_n = 0;
	i = 1;
	if (ft_strcmp(t_exec->cmd[1], "-n") == 0)
	{
		slash_n = 1;
		i++;
	}
	fd_open = ft_prelim_loop(t_exec, fd, 1);
	if (t_exec->redirect == NULL && p == 1)
		fd_open = 5;
		if (fd_open == EXIT_FAILURE && t_exec->redirect->redirect == LESS)
			return (EXIT_FAILURE);
	ft_echo_redirect(fd_open, t_exec->cmd + i, ok, slash_n);
	return (EXIT_SUCCESS);
}
