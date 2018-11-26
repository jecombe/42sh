/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 06:20:38 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 10:07:20 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	ft_env_flags(const char **cmd, char *flag, int *idx)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (cmd[++i])
	{
		if (cmd[i][++j] != '-')
			break ;
		while (cmd[i][++j])
		{
			if (cmd[i][j] != 'i')
				return (ft_bierrors("env", &cmd[i][j], BIFLAG));
			*flag = 'i';
		}
		j = -1;
	}
	*idx = i;
	return (EXIT_SUCCESS);
}

static int	ft_assign_env(const char **cmd, char flag, int *idx)
{
	char	**grid;

	grid = NULL;
	if (flag == 'i')
		ft_tabdel(&g_env);
	while (cmd[*idx])
	{
		if (!(ft_strchr(cmd[*idx], '=')))
			break ;
		if (!(grid = ft_strsplit(cmd[*idx], '=')))
			return (EXIT_FAILURE);
		ft_setenv(grid[0], grid[1]);
		ft_tabdel(&grid);
		(*idx)++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_exec_env(const char **cmd, int i)
{
	char	**args;
	char	*line;
	int		ret;

	args = NULL;
	line = NULL;
	ret = 0;
	while (cmd[i])
	{
		line = ft_strjoin_free(line, (char *)cmd[i++]);
		line = ft_strjoin_free(line, " ");
	}
	ret = line ? heart_of_101sh(line, 0) : 0;
	ft_strdel(&line);
	return (ret);
}

static int	manage_env(t_op *exec, int *ret)
{
	char	**env;
	char	**set;
	char	flag;
	int		i;

	i = 0;
	flag = '\0';
	if (!(env = ft_tabdup(g_env)))
		return (EXIT_FAILURE);
	if (!(set = ft_tabdup(g_set)))
		return (EXIT_FAILURE);
	if (ft_env_flags((const char **)exec->cmd, &flag, &i))
		return (EXIT_FAILURE + ft_tabdel(&env) + ft_tabdel(&set));
	if (ft_assign_env((const char **)exec->cmd, flag, &i))
		return (EXIT_FAILURE + ft_tabdel(&env) + ft_tabdel(&set));
	*ret = ft_exec_env((const char **)exec->cmd, i);
	ft_tabdel(&g_env);
	ft_tabdel(&g_set);
	g_env = env;
	g_set = set;
	return (0);
}

int			ft_env(t_op *exec)
{
	int		ret;

	ret = 0;
	if (!exec || exec->cmd[1] == NULL)
		ft_print_env();
	else if (manage_env(exec, &ret))
		return (EXIT_FAILURE);
	return (ret);
}
