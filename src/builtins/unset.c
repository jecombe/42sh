/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unset.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:52:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 19:28:02 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

int				ft_unset_var(char *cmd)
{
	int			i;
	int			j;

	i = 0;
	if (cmd && g_set)
		while (g_set && g_set[i])
		{
			j = 0;
			while (g_set[i][j] && cmd[j] && g_set[i][j] == cmd[j])
				j++;
			if (j > 0 && g_set[i][j] == '=' && j == (int)ft_strlen(cmd))
				return (ft_strdel_in_tab(&g_set, i));
			i++;
		}
	return (0);
}

/*
 * LES REDIRECTIONS NE SONT PAS FAITES
*/
int				unset(t_op *exec, int fd_open)
{
	int		i;

	i = 1;
	if (exec->cmd)
	{
		while (exec->cmd[i])
		{
			ft_unset_var(exec->cmd[i]);
			ft_unsetenv(exec->cmd[i++], fd_open);
		}
	}
	return (0);
}
