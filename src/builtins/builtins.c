/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:33:04 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 04:40:51 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/builtins.h"

int		ft_builtins(t_op *exec, int what, int flag)
{
	t_hashtable *hashtable = NULL;

	if (ft_strcmp(exec->cmd[0], "ft_assign") == 0)
		return (ft_assign(exec));
	else
		ft_save_hash(&hashtable);
	if (ft_strcmp(exec->cmd[0], "echo") == 0)
		if (ft_echo(exec, flag))
			return (EXIT_FAILURE);
	if (ft_strcmp(exec->cmd[0], "cd") == 0)
		if (ft_cd(exec, flag))
			return (EXIT_FAILURE);
	if (ft_strcmp(exec->cmd[0], "exit") == 0)
		if (ft_exit(exec, flag))
			return (EXIT_FAILURE);
	if (ft_strcmp(exec->cmd[0], "env") == 0)
		if (ft_env(exec))
			return (EXIT_FAILURE);
	if (ft_strcmp(exec->cmd[0], "setenv") == 0)
	{
		if (!exec->cmd[1])
			return (ft_setenv(NULL, NULL));
		if (exec->cmd[2] && exec->cmd[3])
				return (ft_bierrors("setenv", NULL, BITOMANY));
		ft_setenv(exec->cmd[1], exec->cmd[2]);
	}
	if (ft_strcmp(exec->cmd[0], "unsetenv") == 0)
		return (ft_unsetenv(exec->cmd[1]));
	if (ft_strcmp(exec->cmd[0], "set") == 0)
		return (set(exec));
	if (ft_strcmp(exec->cmd[0], "unset") == 0)
		return (unset(exec));
	if (ft_strcmp(exec->cmd[0], "export") == 0)
		return (ft_export(exec));
	if (ft_strcmp(exec->cmd[0], "hash") == 0)
	{
		ft_hash_print(hashtable);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
