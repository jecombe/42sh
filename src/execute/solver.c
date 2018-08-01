/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:01:17 by jecombe     ###    #+. /#+    ###.fr     */
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
	if (t_exec->cmd[0])
	{
		ft_skip(t_exec->cmd);
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		//printf("LLLLLLLLLLLLLL %s\n", tmp_bin);
		ft_exec(t_exec, env, tmp_bin);
	}
	while (t_exec)
	{
		printf("==============> %s\n", t_exec->cmd[0]);
		t_exec = t_exec->next;
	}
}
