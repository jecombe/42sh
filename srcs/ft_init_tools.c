/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_tools.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 06:54:51 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/08 14:55:12 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int					ft_isquote(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == '`' || ch == '\'' || ch == '"')
		return (1);
	return (0);
}

int					ft_isbashop(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == ';')
	{
		/*if (c == '>')
		{
			printf("CHEVRON %d\n", g_chevron);
			g_chevron = 1;
		}*/
		return (1);
	}
	return (0);
}

static char			*ft_isbin_pathconstruct(const char *path,
		const char *target)
{
	char			buff[1024];
	char			*s;

	ft_bzero(buff, 1024);
	s = NULL;
	ft_strcpy(buff, path);
	if (buff[ft_strlen(buff) - 1] != '/')
		ft_strcat(buff, "/");
	ft_strcat(buff, target);
	s = ft_strdup(buff);
	return (s);
}

static int			ft_isbin_check(const char *cmd, const char *path)
{
	t_read			read;
	char			*pathsrc;

	pathsrc = NULL;
	if ((read.dir = opendir(path)))
	{
		while ((read.ent = readdir(read.dir)))
			if (ft_strcmp(read.ent->d_name, cmd) == 0)
			{
				pathsrc != NULL ? ft_strdel(&pathsrc) : 0;
				pathsrc = ft_isbin_pathconstruct(path, cmd);
				if (access(pathsrc, X_OK) == 0)
				{
					closedir(read.dir);
					ft_strdel(&pathsrc);
					return (1);
				}
			}
		closedir(read.dir);
	}
	return (0);
}

char				*ft_isbin(const char *cmd)
{
	int				i;
	char			*s;
	char			*path;
	char			**array;

	i = -1;
	s = NULL;
	if (access(cmd, X_OK) == 0)
	{
		s = ft_strdup(cmd);
		return (s);
	}
	path = ft_getenv("PATH");
	if ((array = ft_strsplit(path, ':')))
		while (array[++i])
		{
			if (ft_isbin_check(cmd, array[i]))
			{
				s = ft_isbin_pathconstruct(array[i], cmd);
				break ;
			}
		}
	array ? ft_stradel(&array) : 0;
	path ? ft_strdel(&path) : 0;
	return (s);
}
