/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   envset_add.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:57:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 14:43:10 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		sort_set(void)
{
	int		size;
	int		i;
	int		k;
	char	*tmp;

	size = ft_tablen(g_set);
	i = -1;
	k = size + 1;
	tmp = NULL;
	while (--k != 0)
	{
		while (++i != (k - 1))
		{
			if (ft_strcmp(g_set[i], g_set[i + 1]) > 0)
			{
				tmp = ft_strdup(g_set[i]);
				ft_strdel(&g_set[i]);
				g_set[i] = ft_strdup(g_set[i + 1]);
				ft_strdel(&g_set[i + 1]);
				g_set[i + 1] = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
		}
		i = -1;
	}
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
	if (!g_set || !(s = ft_envset_line((const char **)g_set, name)))
	{
		if (!(ft_malloc_cmd(&g_set, s = ft_envset_join(name, value))))
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
	if (!g_env || !(s = ft_envset_line((const char **)g_env, name)))
		ft_malloc_cmd(&g_env, (s = ft_envset_join(name, value)));
	else
	{
		while (g_env[++i])
			if ((ft_strcmp(g_env[i], s)) == 0)
				break ;
		ft_strdel(&g_env[i]);
		g_env[i] = ft_envset_join(name, value);
	}
	add_to_set(name, value);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
