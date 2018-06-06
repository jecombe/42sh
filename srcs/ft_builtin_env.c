/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_env.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:27:40 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 02:43:07 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int			ft_builtin_unsetenv(const char *name)
{
	int		i;
	int		f;
	char	*tmp;
	char	*s;
	char	*env[100];

	i = -1;
	f = -1;
	if (!(tmp = ft_getenv(name)))
		return (ft_error_env(name, 5));
	s = ft_builtin_join(name, tmp);
	while (g_env[++i] && (i < 100))
		if (ft_strcmp(g_env[i], s) != 0)
			env[++f] = ft_strdup(g_env[i]);
	while (++f && (f < 100))
		env[f] = NULL;
	ft_env_new((const char **)env);
	i = -1;
	while (env[++i] && (i < 100))
		ft_strdel(&env[i]);
	ft_strdel(&tmp);
	ft_strdel(&s);
	return (0);
}

int			ft_builtin_setenv(const char *name, const char *value)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	s = NULL;
	if ((tmp = ft_getenv(name)))
		s = ft_builtin_join(name, tmp);
	while (g_env[++i] && (i < 100))
		if (s != NULL)
			if (ft_strcmp(g_env[i], s) == 0)
				break ;
	s != NULL ? ft_strdel(&g_env[i]) : 0;
	g_env[i] = ft_builtin_join(name, value);
	tmp != NULL ? ft_strdel(&tmp) : 0;
	s != NULL ? ft_strdel(&s) : 0;
	return (0);
}

int			ft_builtin_env(void)
{
	int		i;

	i = -1;
	while (g_env[++i])
		ft_putendl(g_env[i]);
	return (0);
}
