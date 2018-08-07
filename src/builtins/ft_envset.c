/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_envset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/07 00:42:49 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/07 04:10:33 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

char		*ft_envset_line(const char **envset, const char *name)
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
			s = ft_strdup(envset[i]);
		ft_strdel(&tmp);
		if (s)
			break ;
	}
	return (s);
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
	ft_env();
	return (s);
}

char		*ft_envset_join(const char *name, const char *value)
{
	char	*tmp;
	char	*s;

	tmp = NULL;
	s = NULL;
	tmp = ft_strjoin(name, "=");
	s = ft_strjoin(tmp, value);
	ft_strdel(&tmp);
	return (s);
}
