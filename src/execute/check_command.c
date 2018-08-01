/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_command.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 04:29:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:32:29 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
int			ft_check_command(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	else if (ft_strcmp("cd", cmd) == 0)
		return (2);
	else if (ft_strcmp("exit", cmd) == 0)
		return (3);
	else if (ft_strcmp("env", cmd) == 0)
		return (4);
	else if (ft_strcmp("setenv", cmd) == 0)
		return (5);
	else if (ft_strcmp("unsetenv", cmd) == 0)
		return (6);
	else
		return (0);

}

void		ft_builtins(t_op *t_exec, int what)
{
	if (what == 1)
		printf("ECHO\n");
	if (what == 2)
		printf("CD\n");
	if (what == 3)
		printf("EXIT\n");
	if (what == 4)
		printf("ENV\n");
	if (what == 5)
		printf("SETENV\n");
	if (what == 6)
		printf("UNSETENV\n");;
}


