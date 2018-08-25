/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_to_env.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 06:52:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 10:10:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/init.h"

static int			not_found(char *to_add)
{
	int			j;
	char		*tmp;

	if (g_env && g_env[0])
	{
		if ((j = index_to_var("_", g_env)) >= 0)
		{
			tmp = ft_strdup(g_env[j]);
			ft_strdel(&g_env[j]);
			g_env[j] = ft_strdup(to_add);
			ft_malloc_cmd(&g_env, tmp);
		}
		else
			ft_malloc_cmd(&g_env, to_add);
	}
	else
		ft_malloc_cmd(&g_env, to_add);
	return (0);
}

int					add_to_env(char *name, char *value)
{
	int			i;
	int			j;
	int			find;
	char		*to_add;

	find = 0;
	i = 0;
	to_add = concat_name_value(name, value);
	if (g_env)
		while (g_env[i] && find == 0)
		{
			j = 0;
			while (g_env[i][j] == name[j] && g_env[i][j] && name[j])
				j++;
			g_env[i][j] == '=' && j != 0 ? find = 1 : i++;
		}
	if (find == 1)
	{
		ft_strdel(&g_env[i]);
		g_env[i] = ft_strdup(to_add);
	}
	else
		not_found(to_add);
	ft_strdel(&to_add);
	return (0);
}
