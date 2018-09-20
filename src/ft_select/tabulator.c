/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 16:48:41 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		add_bin(char ***bin, DIR *dir, char *line, int version)
{
	struct dirent	*t_dir;

	while ((t_dir = readdir(dir)))
	{
		if ((line && 0 == ft_strncmp(line, t_dir->d_name, ft_strlen(line))) ||
			!line || version == 1)
		{
			printf("\nELEMENT TROUVER == %s\n", t_dir->d_name);
			sleep(1);
			ft_malloc_cmd(bin, t_dir->d_name);
		}
		else
			printf("\n!!ELEMENT TROUVER == %s LINE == %s\n", t_dir->d_name, line);
	}
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
					add_bin(&bin, dir, line, 0);
					closedir(dir);
				}
			ft_strdel(&tmp);
			ft_tabdel(&path);
		}
	}
	return (bin);
}

int		check_dir(char **path, char *word)
{
	char		*tmp;

	tmp = NULL;
	printf("PATH == %s, WORD == %s\n", *path, word);
	if (*path)
	{
		if ((*path)[ft_strlen(*path) - 1] == '/')
		{
			printf("CHECK_DIR == 0\n");
			if (ft_strlen(*path) - 1 > 0)
				tmp = ft_strsub(*path, 0, ft_strlen(*path) - 1);
			else
				tmp = ft_strdup("/");
			if (!ft_isdir(tmp))
			{
				ft_strdel(&tmp);
				return (-1);
			}
			ft_strdel(path);
			*path = ft_strdup(tmp);
			ft_strdel(&tmp);
			return (1);
		}
		else
		{
			printf("CHECK_DIR == 1\n");
			tmp = ft_strsub(*path, 0, ft_strlen(*path) - ft_strlen(ft_strrchr(*path, '/') + 1));
			if (!ft_isdir(tmp))
				return (-1);
			ft_strdel(path);
			*path = ft_strdup(tmp);
		}
		return (0);
	}
	return (-1);
}

int		search_little_word(char **str, char *word)
{
	char	*tmp;

	if (word && word[ft_strlen(word) - 1] != '/')
	{
		printf("TRUC == %c\n", word[ft_strlen(word) - 1]);
		printf("WORD == %s\n", word);
		if (word[0] == '/')
		{
			printf("0TRUC == %s\n", ft_strrchr(word, '/') + 1);
			*str = ft_strdup(ft_strrchr(word, '/') + 1);
		}
		else
			*str = ft_strdup(word);
	}
	else
		ft_strdel(str);
	return (0);
}

char	**search_in_rep(char *word)
{
	char		**bin;
	char		*path;
	DIR			*dir;
	int			ret;

	ret = 0;
	bin = NULL;
	printf("WORD == %s\n", word);
	if (word)
	{
		if (word[0] == '/')
			path = ft_strdup(word);
		else
			path = ft_search_pwd(word);
		if ((ret = check_dir(&path, word)) == -1)
		{
			printf("CHECK DIR == -1\n");
			ft_strdel(&path);
			return (NULL);
		}
	}
	else
		path = ft_search_pwd(NULL);
	if ((dir = opendir(path)))
	{
		printf("\nOPENDIR PATH == %s\n", path);
		search_little_word(&path, word);
		printf("\nELEMENT A RECHERCHER == %s\n", path);
		add_bin(&bin, dir, path, ret);
		closedir(dir);
	}
	return (bin);
}

int		echap_char(char ***element)
{
	int		i;
	int		j;

	i = -1;
	while ((*element)[++i])
	{
		j = -1;
		while ((*element)[i][++j])
			if (ft_isechap((*element)[i][j]))
				ft_add_to_str(&(*element)[i], '\\', j++);
		printf("ELEMENT[%d] == %s\n", i, (*element)[i]);
	}
	return (0);
}

char	**lexer_tab(char *line)
{
	char	**ret;
	int		i = 0;
	int		j;

	i = 0;
	ret = ft_strsplit(line, ' ');
	/*
	printf("\n");
	while (line[i])
	{
		j = i++;
//		if (ft_isbegintab(line[i], i > 0 ? line[i - 1] : 0, i))
//		{
			while (ft_isendtab(line[j], line[i], i == j  + 1 ? 0 : line[i - 1], (int[2]) {j, i}))
				i++;
				printf("LEXER == |%s|\n\n", ft_strsub(line, j, i - j));
			if (line[i])
			i++;
//		}
//		else
//			i++;
	}
	ret = NULL;*/
	return (ret);
}

int		tabulator(t_editor **ed)
{
	int		nb_word;
	char	*word;
	char	**element;
	char	**tmpline;

	tmpline = lexer_tab((*ed)->line);
	word = NULL;
	/*
	if ((nb_word = search_word(&word, ed)) > -1)
	{
		printf("WORD == %s NB_WORD == %d\n", word, nb_word);
		sleep(2);
//		word = ft_strdup("n");
		if (nb_word <= 1)
			element = search_bin((*ed)->line);
		else if (nb_word)
			element = search_in_rep(word);
		echap_char(&element);
	}*/
	printf("LINE == %s NB_WORD == %d\n", (*ed)->line, nb_word);
	sleep(2);
	return (0);
}
