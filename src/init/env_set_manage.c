
#include "../../include/heart.h"

int			ft_envset_add(char ***envset, char *new_arg)
{
	int		i;
	char	**grid;

	i = 0;
	grid = NULL;
	if (!new_arg)
		return (EXIT_FAILURE);
	if (*envset)
		if (!(grid = ft_tabdup(*envset)))
			return (EXIT_FAILURE);
	(*envset) ? ft_tabdel(&(*envset)) : 0;
	if (!((*envset) = (char **)malloc(sizeof(char *) * (ft_tablen(grid) + 2))))
		return (EXIT_FAILURE);
	if (grid)
		while (grid[i])
		{
			(*envset)[i] = ft_strdup(grid[i]);
			i++;
		}
	(*envset)[i] = ft_strdup(new_arg);
	(*envset)[i + 1] = NULL;
	return (EXIT_SUCCESS);
}

char		*ft_envset_value(const char **envset, const char *name)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	tmp = NULL;
	s = NULL;
	while (envset[++i])
	{
		tmp = ft_strsub(envset[i], 0, ft_strlen(name));
		if (ft_strcmp(name, tmp) == 0 && envset[i][ft_strlen(name)] == '=')
			s = ft_strdup(ft_strchr(envset[i], '=') + 1);
		ft_strdel(&tmp);
		if (s)
			break ;
	}
	return (s);
}

char		*ft_envset_line(const char **envset, const char *name)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	tmp = NULL;
	s = NULL;
	if (envset)
		while (envset[++i])
		{
			tmp = ft_strsub(envset[i], 0, ft_strlen(name));
			if (ft_strcmp(name, tmp) == 0 && envset[i][ft_strlen(name)] == '=')
				s = ft_strdup(envset[i]);
			ft_strdel(&tmp);
			if (s)
				break ;
		}
	return (s);
}

char		*ft_envset_join(const char *name, const char *value)
{
	char	*tmp;
	char	*s;

	tmp = NULL;
	s = NULL;
	tmp = ft_strjoin(name, "=");
	if (value)
		s = ft_strjoin(tmp, value);
	else
		s = ft_strjoin(tmp, "''");
	ft_strdel(&tmp);
	return (s);
}

int			ft_setenv(const char *name, const char *value, int fd_open)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_env, name)))
		ft_envset_add(&g_env, (s = ft_envset_join(name, value)));
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

int			ft_set(const char *name, const char *value, int fd_open)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_set, name)))
		ft_envset_add(&g_set, (s = ft_envset_join(name, value)));
	else
	{
		while (g_set[++i])
			if ((ft_strcmp(g_set[i], s)) == 0)
				break ;
		ft_strdel(&g_env[i]);
		g_env[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}

int			ft_unsetenv(const char *name, int fd_open)
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
	g_env = NULL;
	while (env[++i])
		if (!(ft_strcmp(env[i], s) == 0))
			ft_envset_add(&g_env, env[i]);
	ft_tabdel(&env);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}

int			ft_envset_exist(const char **envset, const char *name)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (envset[++i])
	{
		if (!(tmp = ft_strsub(envset[i], 0, ft_strlen(name))))
			return (EXIT_FAILURE);
		if ((ft_strcmp(name, tmp) == 0) && (envset[i][ft_strlen(name)] == '='))
			break ;
		ft_strdel(&tmp);
	}
	(tmp) ? ft_strdel(&tmp) : 0;
	if (!envset[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


