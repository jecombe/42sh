/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 01:54:40 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/execute.h"

void		ft_solver(t_op *tmp_op, char **env)
{
	ft_get_bin(env);
	char *tmp_bin;
	if (tmp_op->cmd[0])
	{
		ft_skip_n(tmp_op->cmd);
		tmp_bin = ft_search_bin(tmp_op->cmd[0]);
		//printf("LLLLLLLLLLLLLL %s\n", tmp_bin);
		ft_exec(tmp_op, env, tmp_bin);
	}
	while (tmp_op)
	{
		printf("==============> %s\n", tmp_op->cmd[0]);
		tmp_op = tmp_op->next;
	}
}
