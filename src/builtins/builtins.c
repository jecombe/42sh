/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:33:04 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 14:56:52 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int		ft_builtins(t_op *t_exec, int what, int flag)
{
	if (what == 1)
		if (ft_echo(t_exec, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	if (what == 2)
		if (ft_cd(t_exec, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	if (what == 3)
		if (ft_exit(t_exec, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	if (what == 4)
		if (ft_env(t_exec, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	if (what == 5)
		if (ft_setenv(t_exec, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	if (what == 6)
		if (ft_unsetenv(t_exec, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
