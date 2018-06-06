/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_cd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:30:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 03:03:35 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./minishell.h"

static char		*ft_builtin_cd_pathconstruct(const char *path)
{
	char		*s;
	char		*tmp;

	s = NULL;
	tmp = NULL;
	if (path == NULL || ft_strcmp(path, "~") == 0)
		s = ft_getenv("HOME");
	else if (path[0] == '~' && path[1] == '/')
	{
		tmp = ft_getenv("HOME");
		s = ft_strjoin(tmp, ft_strchr(path, '/'));
		ft_strdel(&tmp);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		s = ft_getenv("OLDPWD");
		ft_putendl(s);
	}
	else
		s = ft_strdup(path);
	return (s);
}

int				ft_builtin_cd(const char *path)
{
	char		buff[1024];
	char		*s;
	char		*tmp;

	ft_bzero(buff, 1024);
	s = ft_builtin_cd_pathconstruct(path);
	if (chdir(s) == -1)
	{
		ft_strcpy(buff, s);
		ft_strdel(&s);
		return (ft_error_cd(buff, 2));
	}
	tmp = ft_getenv("PWD");
	getcwd(buff, 1024);
	ft_builtin_setenv("PWD", buff);
	ft_builtin_setenv("OLDPWD", tmp);
	ft_strdel(&tmp);
	ft_strdel(&s);
	return (0);
}
