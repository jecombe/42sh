/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_manage.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/08 12:06:40 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/21 21:21:17 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env_new(const char **environ)
{
	int		i;

	i = -1;
	ft_env_del();
	while (environ[++i] && (i < 100))
		g_env[i] = ft_strdup(environ[i]);
	while (i < 100)
		g_env[i++] = NULL;
}

char		*ft_getenv(const char *name)
{
	int		i;
	char	*s;
	char	*tmp;

	i = -1;
	s = NULL;
	tmp = NULL;
	while (g_env[++i] && (i < 100))
	{
		tmp = ft_strsub(g_env[i], 0, ft_strlen(name));
		if (ft_strcmp(tmp, name) == 0 && g_env[i][ft_strlen(name)] == '=')
			s = ft_strdup(ft_strchr(g_env[i], '=') + 1);
		ft_strdel(&tmp);
	}
	return (s);
}

void		ft_env_del(void)
{
	int		i;

	i = -1;
	while (g_env[++i] && (i < 100))
		ft_strdel(&(g_env[i]));
}
