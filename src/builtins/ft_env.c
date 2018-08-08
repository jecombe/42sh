/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 04:42:06 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 02:12:10 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

int			ft_env(void)
{
	int		i;

	i = -1;
	while (g_env[++i])
		ft_putendl(g_env[i]);
	return (EXIT_SUCCESS);
}

int			ft_setenv(int overwrite)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (ft_env());
	if (strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_env, name)))
		ft_malloc_cmd(&g_env, (s = ft_envset_join(name, value)));
	else if (overwrite)
	{
		while (g_env[++i])
			if ((ft_strcmp(g_env[i], s)) == 0)
				break;
		ft_strdel(&g_env[i]);
		g_env[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}

int			ft_unsetenv(const char *name)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_env, name)))
		return (EXIT_SUCCESS);
	env = ft_tabdup(g_env);
	ft_tabdel(&g_env);
	while (env[++i])
		if (!(ft_strcmp(env[i], s) == 0))
			ft_malloc_cmd(&g_env, env[i]);
	ft_tabdel(&env);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
