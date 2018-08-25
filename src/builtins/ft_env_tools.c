/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 06:30:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 10:28:19 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

char		*ft_get_var(char *line)
{
	int		i;

	i = 0;
	if (line)
		while (line[i])
		{
			if (line[i] == '=')
				return (ft_strsub(line, 0, i));
			i++;
		}
	return (NULL);
}

char		*ft_get_value(char *line)
{
	int		i;

	i = 0;
	if (line)
		while (line[i])
		{
			if (line[i] == '=' && line[i] + 1)
				return (ft_strdup(line + (i + 1)));
			i++;
		}
	return (NULL);
}

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
