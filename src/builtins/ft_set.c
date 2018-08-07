/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 04:42:06 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/07 05:11:09 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

int			ft_set(void)
{
	int		i;

	i = -1;
	while (g_set[++i])
		ft_putendl(g_set[i]);
	return (EXIT_SUCCESS);
}

int			ft_export(const char *name, const char *value)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (ft_set());
	if (strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_set, name)))
		ft_malloc_cmd(&g_set, (s = ft_envset_join(name, value)));
	else
	{
		while (g_set[++i])
			if ((ft_strcmp(g_set[i], s)) == 0)
				break;
		ft_strdel(&g_set[i]);
		g_set[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}

int			ft_unset(const char *name)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_set, name)))
		return (EXIT_SUCCESS);
	env = ft_tabdup(g_set);
	ft_tabdel(&g_set);
	while (env[++i])
		if (!(ft_strcmp(env[i], s) == 0))
			ft_malloc_cmd(&g_set, env[i]);
	ft_tabdel(&env);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
