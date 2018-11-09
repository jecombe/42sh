/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tab_manage_path.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:38:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 10:39:24 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

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
	absolute_path = ft_strsub(line, 0, line[1] ? i : 1);
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
		pwd = ft_search_pwd(NULL);
	else if (ft_strchr(line, '/') && !(line[0] == '/'))
		pwd = ft_search_relative_path(line);
	else
		pwd = ft_search_absolute_path(line);
	return (pwd);
}

int		ft_cut_word_and_before(char **str, char *word, char **before)
{
	int		i;

	if (word && word[ft_strlen(word) - 1] != '/' && ft_strchr(word, '/'))
	{
		ft_strdel(str);
		*str = ft_strdup(ft_strrchr(word, '/') + 1);
		i = ft_strlen(word) - ft_strlen(*str);
		*before = ft_strsub(word, 0, i);
	}
	else if (!ft_strchr(word, '/'))
	{
		ft_strdel(str);
		*str = ft_strdup(word);
	}
	else
	{
		*before = ft_strdup(word);
		ft_strdel(str);
	}
	return (0);
}
