/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:34:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 18:29:50 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int 		ft_echo_redirect(char **cmd, int ok, int slash_n)
{
	int i = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (slash_n == 0 && ok == 0)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);

}

int 		ft_echo(t_op *t_exec)
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
	ft_echo_redirect(t_exec->cmd + i, ok, slash_n);
	return (EXIT_SUCCESS);
}
