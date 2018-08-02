/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:36:49 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int		ft_solver(t_op *t_exec, char **env)
{
	ft_get_bin(env);
	char *tmp_bin;
	int ok = 0;
	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
	{
		if (ft_builtins(t_exec, ok) == 2)
			return (0);
		else
			return (2);
	}
	else
	{
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		if (ft_exec(t_exec, env, tmp_bin) == 0)
			return (0);
		else
		{
			printf("sa retourne 2\n");
			return (2);
		}
	}
	return (0);
}
