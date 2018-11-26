/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unset.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:52:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 03:32:47 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		unset_loop(char *name)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (g_set)
	{
		if (name == NULL)
			return (ft_bierrors("unset", NULL, BITOFEW));
		if (!(s = ft_envset_line((const char **)g_set, name)))
			return (EXIT_SUCCESS);
		env = ft_tabdup(g_set);
		ft_tabdel(&g_set);
		g_set = NULL;
		while (env[++i])
			if (!(ft_strcmp(env[i], s) == 0))
				ft_malloc_cmd(&g_set, env[i]);
		ft_tabdel(&env);
		ft_strdel(&s);
	}
	return (EXIT_SUCCESS);
}

int				unset(t_op *exec)
{
	int		i;

	i = 0;
	while (g_set && exec->cmd[++i])
		unset_loop(exec->cmd[i]);
	i = 0;
	while (g_env && exec->cmd[++i])
		ft_unsetenv(exec->cmd[i]);
	return (EXIT_SUCCESS);
}
