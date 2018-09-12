
# include "heart.h"

static void		sort_set(void)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	*tmp2;

	k = -1;
	if (g_set)
	{
		while (g_set[++k])
		{
			i = -1;
			while (g_set[++i])
			{
				j = i;
				while (g_set[++j] && ft_strcmp(g_set[i], g_set[j]) > 0)
				{
					tmp = ft_strdup(g_set[i]);
					tmp2 = ft_strdup(g_set[j]);
					ft_strdel(&g_set[i]);
					ft_strdel(&g_set[j]);
					g_set[i] = ft_strdup(tmp2);
					g_set[j] = ft_strdup(tmp);
					ft_strdel(&tmp);
					ft_strdel(&tmp2);
				}
			}
		}
	}
}

int				add_to_set(char *name, char *value)
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
	{
		if (!(ft_malloc_cmd(&g_set, (s = ft_envset_join(name, value)))))
			sort_set();
	}
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

int				add_to_env(char *name, char *value)
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
