/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_to_env.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 06:52:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:02:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	not_found(char *to_add)
{
	int		j;
	char	*tmp;

	if (g_env && g_env[0])
	{
		if ((j = index_to_var("_", g_env)) >= 0)
		{
			tmp = ft_strdup(g_env[j]);
			ft_strdel(&g_env[j]);
			g_env[j] = ft_strdup(to_add);
			ft_malloc_cmd(&g_env, tmp);
			ft_strdel(&tmp);
		}
		else
			ft_malloc_cmd(&g_env, to_add);
	}
	else
		ft_malloc_cmd(&g_env, to_add);
	return (0);
}

int			add_to_env(char *name, char *value)
{
	char	*s;
	int		i;

	s = NULL;
	i = -1;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_env, name)))
		ft_malloc_cmd(&g_env, (s = ft_envset_join(name, value)));//not_found((s = ft_envset_join(name, value)));
	else
	{
		while (g_env[++i])
			if ((ft_strcmp(g_env[i], s)) == 0)
				break ;
		ft_strdel(&g_env[i]);
		g_env[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}

int			add_to_set(char *name, char *value)
{
	char	*s;
	int		i;

	s = NULL;
	i = -1;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_set, name)))
		ft_malloc_cmd(&g_set, (s = ft_envset_join(name, value)));
	else
	{
		while (g_set[++i])
			if ((ft_strcmp(g_set[i], s)) == 0)
				break ;
		ft_strdel(&g_set[i]);
		g_set[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
