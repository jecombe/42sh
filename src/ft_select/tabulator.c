/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 06:50:30 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		add_bin(char ***bin, DIR *dir, char *line)
{
	struct dirent	*t_dir;

	while ((t_dir = readdir(dir)))
		if ((line && 0 == ft_strncmp(line, t_dir->d_name, ft_strlen(line))) ||
				!line)
			ft_malloc_cmd(bin, t_dir->d_name);
	return (0);
}

char	**search_bin(char *line)
{
	char		**bin;
	char		*tmp;
	char		**path;
	int			i;
	DIR			*dir;

	i = -1;
	bin = NULL;
	if ((tmp = ft_getenv("PATH", g_env)))
	{
		if ((path = ft_strsplit(tmp, ':')))
		{
			while (path[++i])
				if ((dir = opendir(path[i])))
				{
					add_bin(&bin, dir, line);
					closedir(dir);
				}
			ft_strdel(&tmp);
			ft_tabdel(&path);
		}
	}
	return (bin);
}

int		check_dir(char *path, char *word)
{
	char		*tmp;

	tmp = NULL;
	if (path)
	{
		if (path[ft_strlen(path) - 1] == '/')
		{
			printf("\n00WORD == %s\n", path);
			if (ft_strlen(path) - 1 > 0)
				tmp = ft_strsub(path, 0, ft_strlen(path) - 1);
			else
				tmp = ft_strdup("/");
			if (!ft_isdir(tmp))
			{
				printf("00TMP == %s IS NOT A DIR\n", tmp);
				sleep(2);
				return (1);
			}
			printf("00TMP == %s IS A DIR\n", tmp);
			sleep(2);
		}
		else
		{
			printf("\n11WORD == %s\n", path);
			if (ft_isdir(path))
			{
				printf("11TMP == %s PATH IS A DIRECTORY\n", tmp);
				return (2);
			}
			tmp = ft_strsub(path, 0, ft_strlen(path) - ft_strlen(ft_strrchr(path, '/')));
			if (ft_isdir(tmp))
			{
				printf("11TMP == %s TMP IS A DIRECTORY\n", tmp);
				return (2);
			}
			printf("TMPAFTER == %s\n", tmp);
			return (2);
		}
	}
	else
		printf("\n22WORD == %s\n", path);
	return (!path ? 1 : 0);
}

char	**search_in_rep(char *word)
{
	char		**bin;
	char		*path;
	DIR			*dir;

	bin = NULL;
	if (word)
	{
		if (word[0] == '/')
			path = ft_strdup(word);
		else
			path = ft_search_pwd(word);
		if (check_dir(path, word))
		{
			ft_strdel(&path);
			return (NULL);
		}
	}
	else
		path = ft_search_pwd(NULL);
	if ((dir = opendir(path)))
	{
		add_bin(&bin, dir, word);
		closedir(dir);
	}
	return (bin);
}

int		search_word(char **word, t_editor **ed)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if ((*ed)->line)
	{
		while ((*ed)->line[i] && i < (int)(*ed)->cursor_str_pos)
		{
			if ((i == 0 && ft_istab((*ed)->line[i])) || (i > 0 &&
				ft_isblank((*ed)->line[i - 1]) && ft_istab((*ed)->line[i])))
				count++;
			i++;
		}
		return (count > 0 && ft_isblank((*ed)->line[i - 1]) ? count + 1 : count);
	}
	return (count);
}

int		tabulator(t_editor **ed)
{
	int		nb_word;
	char	*word;
	char	**element;

	word = NULL;
	if ((nb_word = search_word(&word, ed)) > -1)
	{
		if (nb_word <= 1)
			element = search_bin((*ed)->line);
		else if (nb_word)
		{
			word = ft_strdup("bin");
			printf("\nSEARCH IN REP WORD == %s\n", word);
			element = search_in_rep(word);
		}
	}
	printf("LINE == %s NB_WORD == %d\n", (*ed)->line, nb_word);
	sleep(2);
	return (0);
}
