/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_search_tab.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:56:07 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 10:37:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_islink(char *test)
{
	struct stat		stat;

	if (lstat(test, &stat) != -1 && (stat.st_mode & S_IFMT) == S_IFLNK)
		return (1);
	return (0);
}

int		search_bin_tab(t_shell **ed)
{
	char		*tmp;
	char		**path;
	int			i;
	DIR			*dir;

	i = -1;
	if ((tmp = ft_getenv("PATH", g_env)))
	{
		if ((path = ft_strsplit(tmp, ':')))
		{
			while (path[++i])
				if ((dir = opendir(path[i])))
				{
					add_bin_tab(ed, dir, path[i]);
					closedir(dir);
				}
			ft_strdel(&tmp);
			ft_tabdel(&path);
		}
	}
	return (0);
}

int		search_in_rep_tab(t_shell **ed)
{
	char		*path;
	char		*tmp;
	DIR			*dir;

	path = ft_search_path((*ed)->t.word);
	if (path && ft_isdir(path) == 0 && ft_islink(path) == 0)
	{
		ft_strdel(&path);
		return (0);
	}
	if (path && (dir = opendir(path)))
	{
		tmp = ft_strdup((*ed)->t.word);
		ft_cut_word_and_before(&(*ed)->t.word, tmp, &(*ed)->t.before);
		ft_strdel(&tmp);
		add_bin_tab(ed, dir, path);
		ft_strdel(&path);
		closedir(dir);
	}
	return (0);
}

char	**search_var_tab(char *word)
{
	char	**ret;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;

	i = -1;
	ret = NULL;
	tmp = word[1] ? ft_strdup(word + 1) : NULL;
	if (g_set)
		while (g_set[++i])
			if (!tmp || (tmp && 0 == ft_strncmp(tmp, g_set[i], ft_strlen(tmp))))
			{
				tmp2 = ft_get_var(g_set[i]);
				tmp3 = ft_strjoin("$", tmp2);
				ft_malloc_cmd(&ret, tmp3);
				ft_strdel(&tmp2);
				ft_strdel(&tmp3);
			}
	ft_strdel(&tmp);
	return (ret);
}
