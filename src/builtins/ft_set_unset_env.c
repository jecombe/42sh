/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_set_unset_env.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/19 09:06:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:39:11 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_setenv(const char *name, const char *value)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (ft_env((t_op *) 0 ));
	if (ft_strchr(name, '='))
		return (ft_bierrors("setenv", NULL, BIEQUAL));
	if (!(s = ft_envset_line((const char **)g_env, name)))
		ft_malloc_cmd(&g_env, (s = ft_envset_join(name, value)));
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

int			ft_unsetenv(const char *name)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (ft_bierrors("unsetenv", NULL, BITOFEW));
	if (!(s = ft_envset_line((const char **)g_env, name)))
		return (EXIT_SUCCESS);
	env = ft_tabdup(g_env);
	ft_tabdel(&g_env);
	g_env = NULL;
	while (env[++i])
		if (!(ft_strcmp(env[i], s) == 0))
			ft_malloc_cmd(&g_env, env[i]);
	ft_tabdel(&env);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
