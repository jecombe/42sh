/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsetenv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 04:13:57 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 17:03:30 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

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
