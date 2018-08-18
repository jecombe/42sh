/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 06:20:38 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/13 04:48:05 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

char		**ft_assign_env(char **cmd, int *idx)
{
	int		i;
	char	**env;
	char	**grid;

	i = 0;
	env = NULL;
	grid = NULL;
/*	if (cmd[1][i] == '-')
	{
		while (cmd[1][++i])
			if (cmd[1][i] != 'i')
				return (NULL);
		if (!(env = ft_tabdup(g_env)))
			return (NULL);
		ft_tabdel(&g_env);
		if (!(g_env = (char **)malloc(sizeof(char *))))
			return (NULL);
		g_env[0] = NULL;
	}
	i = 1;
	while (cmd[++i] && ft_strchr(cmd[i], '='))
	{
		if (!(grid = ft_strsplit(cmd[i], '=')))
			return (NULL);
		printf("<%s><%s>\n", grid[0], grid[1]);
		ft_setenv(grid[0], grid[1]);
	}*/
	if (!(env = ft_tabdup(g_env)))
		return (NULL);
	while (cmd[++i] && ft_strcmp(cmd[i], "-i") == 0)
		ft_tabdel(&g_env);
	if (!g_env)
	{
		if (!(g_env = (char **)malloc(sizeof(char *) * 1)))
			return (NULL);
		else
			g_env[0] = NULL;
	}
	while (cmd[i] && ft_strchr(cmd[i], '='))
	{
		if (!(grid = ft_strsplit(cmd[i++], '=')))
			return (NULL);
		ft_setenv(grid[0], grid[1]);
		ft_tabdel(&grid);
	}
	*idx = i;
	return (env);
}

int			ft_env(t_op *exec)
{
	int		i;
	char	**env;
	char	**cmd;

	i = -1;
	env = NULL;
	cmd = NULL;
	if (!exec || exec->cmd[1] == NULL)
		while (g_env[++i])
			ft_putendl_fd(g_env[i], STDOUT_FILENO);
	/*else
	{
		if (!(env = ft_assign_env(exec->cmd, &i)))
			return (EXIT_FAILURE);
		while (exec->cmd[i])
		ft_malloc_cmd(&cmd, exec->cmd[i++]);
		ft_tabdel(&cmd);
		ft_tabdel(&g_env);
		g_env = ft_tabdup(env);
		ft_tabdel(&env);
	}*/
	return (EXIT_SUCCESS);
}

