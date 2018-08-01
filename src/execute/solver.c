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

void		ft_solver(t_seq *tmp_seq, char **env)
{
	ft_get_bin(env);
	char *tmp_bin;
	t_op *t_exec;
	t_exec = tmp_seq->op;
	int ok = 0;
	if (t_exec->cmd[0])
	{
		if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
			ft_builtins(t_exec, ok);
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		ft_exec(t_exec, env, tmp_bin);
	}
}
