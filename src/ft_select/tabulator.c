/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 17:26:38 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		echap_char(char **element)
{
	int		i;

	i = -1;
	while ((*element)[++i])
		if (ft_isechap((*element)[i]))
			ft_add_to_str(&*element, '\\', i++);
//	printf("ELEMENT_ECHAPER == %s\n", *element);
	return (0);
}

int		add_bin(char ***bin, DIR *dir, char *line, int version)
{
	struct dirent	*t_dir;
	char			*tmp;

	while ((t_dir = readdir(dir)))
	{
		tmp = NULL;
		tmp = ft_strdup(t_dir->d_name);
		echap_char(&tmp);
		if ((line && 0 == ft_strncmp(line, tmp, ft_strlen(line))) ||
//		if ((line && 0 == ft_strstr(tmp, line)) ||
			!line || version == 1)
		{
//			printf("ELEMENT TROUVER\n");
//			sleep(1);
			ft_malloc_cmd(bin, tmp);
		}
//		else
//			printf("\n!!ELEMENT TROUVER == %s LINE == %s\n", t_dir->d_name, line);
		ft_strdel(&tmp);
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
//	printf("PATH == %s, WORD == %s\n", *path, word);
	if (*path)
	{
		if ((*path)[ft_strlen(*path) - 1] == '/')
		{
//			printf("CHECK_DIR == 0\n");
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
//			printf("CHECK_DIR == 1\n");
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
//		printf("TRUC == %c\n", word[ft_strlen(word) - 1]);
//		printf("WORD == %s\n", word);
		if (word[0] == '/')
		{
//			printf("0TRUC == %s\n", ft_strrchr(word, '/') + 1);
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
//	printf("WORD == %s\n", word);
	if (word)
	{
		if (word[0] == '/')
			path = ft_strdup(word);
		else
			path = ft_search_pwd(word);
		if ((ret = check_dir(&path, word)) == -1)
		{
//			printf("CHECK DIR == -1\n");
			ft_strdel(&path);
			return (NULL);
		}
	}
	else
		path = ft_search_pwd(NULL);
	if ((dir = opendir(path)))
	{
//		printf("\nOPENDIR PATH == %s\n", path);
		search_little_word(&path, word);
//		printf("\nELEMENT A RECHERCHER == %s\n", path);
		add_bin(&bin, dir, path, ret);
		closedir(dir);
	}
	return (bin);
}

char	**search_var(char *word)
{
	char	**ret;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	ret = NULL;
//	printf("00\n");
	tmp = word[1] ? ft_strdup(word + 1) : NULL;
	if (g_set)
	{
//	printf("11\n");
		while (g_set[i])
		{
			if ((tmp && 0 == ft_strncmp(tmp, tmp, ft_strlen(tmp))) || !tmp)
			{
				tmp2 = ft_get_value(g_set[i]);
				ft_malloc_cmd(&ret, tmp2);
				ft_strdel(&tmp2);
//				printf("SEARCH_VAR == %s\n", g_set[i]);
			}
			i++;
		}
	}
	ft_strdel(&tmp);
//	printf("22\n");
	return (ret);
}

int		search_end_word(int index, char **tablo)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (tablo)
	{
		while (tablo[i])
		{
			count += ft_strlen(tablo[i]);
			i++;
		}
	}
	return (count);
}

void	binorfile(char **t, int nb_word[2], int *end_word, int cursor_str_pos)
{
	int		i;

	i = 0;
	if (t)
		while (t[i] && *end_word < cursor_str_pos)
		{
			*end_word += ft_strlen(t[i]);
			if (ft_isseparator(t[i][0]))
				nb_word[0] = 0;
			else if (ft_isprint(t[i][0]))
				nb_word[0]++;
			i++;
		}
	nb_word[1] = i;
}

int		lexer_tab(t_editor **ed, char **word, char ***t, int nb_word[2])
{
	int		end_word;

//	*t = ft_tabsplit((*ed)->line, (*ed)->cursor_str_pos);
//	int i = 0;
	(*ed)->t.cmd = ft_tabsplit((*ed)->line, (*ed)->cursor_str_pos);
//	while ((*t)[i])
//	printf("TABUL == %s\n", (*t)[i++]);
//	sleep(2);
	end_word = 0;
//	binorfile(*t, nb_word, &end_word, (*ed)->cursor_str_pos);
	binorfile((*ed)->t.cmd, nb_word, &end_word, (*ed)->cursor_str_pos);
//	printf("\nEND_WORD == %d CURSOR_POS == %d\n", end_word, (int)(*ed)->cursor_str_pos);
//	printf("LINE ACTUELLE == %s NB_WORD[0] == %d NB_WORD[1] == %d\n", (*t)[nb_word[1] - 1], nb_word[0], nb_word[1]);
	if ((*ed)->cursor_str_pos != end_word)
	{
		(*ed)->cursor_str_pos = end_word;
		return (-1);
	}
	//if ((*t) && (*t)[nb_word[1] - 1] && !ft_isseparator((*t)[nb_word[1]][0]))
	*word = ft_strdup((*ed)->t.cmd[nb_word[1] > 0 ? nb_word[1] - 1 : nb_word[1]]);
	if (*word && *word[0] == '$')
		nb_word[0] = -1;
	return (1);
}

int		tabulator(t_editor **ed, int version)
{
	int		nb_word[2];
	char	*word;
	char	**element;
	char	**tmpline;

	(void)version;
	word = NULL;
	tmpline = NULL;
	nb_word[0] = 0;
	nb_word[1] = 0;
	if (lexer_tab(ed, &word, &tmpline, nb_word) != -1)
	{
//		printf("WORD == %s\n", word);
//		sleep(2);
//		word = ft_strdup("n");
		if (nb_word[0] == 1 || nb_word[0] == 0)
			element = search_bin(word);
		else if (nb_word[0] == -1)
			element = search_var(word);
		else
			element = search_in_rep(word);
		if (element && element[1])
		{
//			int i = 0;
//			while (element[i])
//				printf("ELEMENT[i] == %s\n", element[i++]);
			ft_strdel(&word);
			printf("\n\r");
			ft_select(element, &word, &(*ed)->tabu);
//			display_prompt(ft_getenv("HOME", g_set), 0);
			printf("RET_FT_SELECT == %s\n", word);
		}
	}
//	printf("LINE == %s NB_WORD == %d WORD == %s\n", (*ed)->line, nb_word[0], word);
//	sleep(2);
	return (0);
}
