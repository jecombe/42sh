/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 06:07:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 12:57:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		ft_isdir(char *test)
{
	struct stat		stat;

	if (lstat(test, &stat) != -1 && (stat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int		ft_isechap(char c)
{
	if (c == '$' || c == ' ' || c == '/' || c == '*'|| c == '\'' || c == '"' ||
		c == '`' || c == '#' || c == '&' || c == '<' || c == '>' || c == ';' ||
		c == '|' || c == '!' || c == '?' || c == '\\' || c == '~')
		return (1);
	return (0);
}

int		ft_isseparator(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

char	*ft_search_pwd(char *ext)
{
	char	*ret;
	char	pwd[4096];
	char	*tmp;

	ret = NULL;
	getcwd(pwd, sizeof(pwd));
	if (ext)
	{
		tmp = ft_strjoin(pwd, "/");
		ret = ft_strjoin(tmp, ext);
		ft_strdel(&tmp);
	}
	else
		ret = ft_strdup(pwd);
	return (ret);
}

char	*ft_search_absolute_path(char *line)
{
	int		i;
	char	*absolute_path;

	i = ft_strlen(line) - ft_strlen(ft_strrchr(line, '/'));
	absolute_path = ft_strsub(line, 0, i);
	return (absolute_path);
}

char	*ft_search_relative_path(char *line)
{
	char	*relative_path;
	char	*tmp;
	int		i;

	i = ft_strlen(line) - ft_strlen(ft_strrchr(line, '/'));
	tmp = ft_strsub(line, 0, i);
	relative_path = ft_search_pwd(tmp);
	ft_strdel(&tmp);
	return (relative_path);
}

char	*ft_search_path(char *line)
{
	char	*pwd;

	if (!line || !ft_strchr(line, '/'))
	{
	printf("0LINE == %s\n", line);
		pwd = ft_search_pwd(NULL);
	}
	else if (ft_strchr(line, '/') && !(line[0] == '/'))
	{
		pwd = ft_search_relative_path(line);
		printf("1LINE == %s\n", line);
	}
	else
	{
	printf("2LINE == %s\n", line);
		pwd = ft_search_absolute_path(line);
	}
	printf("0PWD == %s\n", pwd);
	sleep(2);
	return (pwd);
}
