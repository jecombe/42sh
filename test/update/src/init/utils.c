/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 06:42:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 09:48:21 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/init.h"

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
int					index_to_var(char *name, char **env)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	if (name && env)
	{
		while (env[++i])
		{
			j = 0;
			while (env[i][j] == name[j] && env[i][j] && name[j])
				j++;
			if (env[i][j] == '=' && j > 0)
				return (i);
		}
	}
	return (-1);
}

static char			*found_slash(int i[2], char *bin, char **tmp_1, char **tmp)
{
	char		*tmp_2;

	if (i[0] > 0 && bin[i[0] - 1] == '/')
	{
		while (i[0] > 0 && bin[i[0]] == '/')
			i[0] = i[0] - 1;
		i[0] = i[0] + 1;
	}
	if (!(i[0] == 0 || (i[0] == 1 && bin[0] == '.')))
	{
		if (bin[0] == '/' || bin[0] == '.')
		{
			while (bin[i[1]] == '.')
				i[1] = i[1] + 1;
			while (bin[i[1]] == '/')
				i[1] = i[1] + 1;
		}
		tmp_2 = ft_strsub(bin, i[1], i[0] - i[1]);
		*tmp_1 = ft_strjoin("/", tmp_2);
		ft_strdel(&tmp_2);
		tmp_2 = ft_strjoin(*tmp, *tmp_1);
		ft_strdel(tmp_1);
		return (tmp_2);
	}
	return (NULL);
}

char				*search_path_of_101sh(char *bin)
{
	char		*tmp;
	char		*tmp_1;
	char		*tmp_2;
	char		buff[4096];
	int			i[2];

	i[1] = 0;
	tmp_1 = NULL;
	tmp = ft_strdup(getcwd(buff, sizeof(buff)));
	if (bin)
	{
		i[0] = ft_strlen(bin);
		while (i[0] >= 0)
		{
			if (bin[i[0]] == '/')
			{
				tmp_2 = found_slash(i, bin, &tmp_1, &tmp);
				tmp_2 ? ft_strdel(&tmp) : 0;
				return (tmp_2 ? tmp_2 : tmp);
			}
			i[0] = !(bin[i[0]] == '/') ? i[0] = i[0] - 1 : i[0];
		}
	}
	return (tmp);
}

char				*concat_name_value(char *name, char *value)
{
	char		*str;
	char		*str2;

	str = NULL;
	str2 = NULL;
	if (!name)
		return (NULL);
	str2 = ft_strjoin(name, "=");
	if (value)
	{
		str = ft_strjoin(str2, value);
		ft_strdel(&str2);
	}
	str ? ft_strdel(&str2) : 0;
	return (str ? str : str2);
}
