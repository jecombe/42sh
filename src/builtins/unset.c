/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unset.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:52:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 06:54:16 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				ft_unset_var(char *cmd)
{
	int			i;
	int			j;

	i = 0;
	while (cmd && g_set && g_set[i])
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

int				unset(t_op *exec)
{
	int		i;

	i = 1;
	if (exec->cmd)
		while (g_set && exec->cmd[i])
		{
			ft_unset_var(exec->cmd[i]);
			ft_unsetenv(exec->cmd[i++]);
		}
	return (0);
}
