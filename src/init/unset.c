/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unset.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:52:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 06:20:44 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/init.h"

char			*get_name_var(char *cmd)
{
	int			i;
	int			j;

	i = 0;
	if (cmd && g_set)
	{
		while (g_set[i])
		{
			j = 0;
			while (g_set[i][j] && cmd[j] && g_set[i][j] == cmd[j])
				j++;
			if (j > 0 && g_set[i][j] == '=' && j + 1 == (int)ft_strlen(cmd))
				return (ft_strsub(g_set[i], 0, j));
			i++;
		}
	}
	return (NULL);
}

int				ft_unset_var(char *cmd)
{
	char			*tmp;
	int				i;

	i = 0;
	tmp = get_name_var(cmd);
	if (g_set && tmp)
	{
		while (g_set[i])
		{
			if (!ft_strcmp(tmp, cmd))
			{
				ft_strdel(&g_set[i]);
				if (i == 0 && !g_set[i + 1])
					ft_tabdel(&g_set);
			}
			i++;
		}
		ft_strdel(&tmp);
	}
	return (0);
}

int				unset(char **cmd)
{
	int		i;

	i = 1;
	if (cmd)
	{
		while (cmd[i])
		{
			ft_unset_var(cmd[i]);
			i++;
		}
	}
	return (0);
}
