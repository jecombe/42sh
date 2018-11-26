/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tab_manage_path.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:38:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 02:26:27 by gmadec      ###    #+. /#+    ###.fr     */
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
	i = i ? i : 1;
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
	char	*tmp;
	char	*tmp2;

	if (line && line[0] == '~' && (tmp2 = ft_getenv("HOME", g_set)))
	{
		if (line[1] == '/')
			tmp = ft_strjoin(tmp2, line + 1);
		else if (!line[1])
			tmp = ft_strdup(tmp2);
		else
			tmp = ft_strdup(line);
		ft_strdel(&tmp2);
	}
	else
		tmp = line ? ft_strdup(line) : NULL;
	if (!tmp || !ft_strchr(tmp, '/'))
		pwd = ft_search_pwd(NULL);
	else if (ft_strchr(tmp, '/') && !(tmp[0] == '/'))
		pwd = ft_search_relative_path(tmp);
	else
		pwd = line && line[0] == '~' && !line[1] ? ft_strdup(tmp) :
			ft_search_absolute_path(tmp);
	ft_strdel(&tmp);
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
