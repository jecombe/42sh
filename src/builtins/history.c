/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 02:27:55 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 11:33:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		save_to_file(char **histsave, char *path)
{
	int		fd;
	int		i;

	i = -1;
	fd = -1;
	if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC)) == -1)
		return (EXIT_FAILURE);
	if (histsave)
		while (histsave[++i])
			ft_putendl_fd(histsave[i], fd);
	return (close(fd) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

static char		*made_history(char *str)
{
	char		*ret;
	int			i;
	int			j;

	j = 0;
	i = 0;
	ret = NULL;
	if (str)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
			return (NULL);
		while (str[i])
		{
			if (i != 0 && str[i + 1])
				ret[j++] = str[i];
			i++;
		}
		ret[j] = '\0';
	}
	return (ret);
}

static int		add_memory(char *news, char ***histsave)
{
	char	*tmp;
	char	*tmp2;
	int		histsize;
	int		histfilesize;

	tmp = ft_getenv("HISTSIZE", g_set);
	histsize = tmp && ft_strisdigit(tmp) ? ft_atoi(tmp) : 500;
	ft_strdel(&tmp);
	histfilesize = *histsave ? ft_tablen(*histsave) + 1: 1;
	while (--histfilesize >= histsize && histfilesize >= 0)
		ft_strdel_in_tab(histsave, 0);
	tmp = ft_itoa(histfilesize == 500 ? histfilesize : histfilesize + 1);
	add_to_set("HISTFILESIZE", tmp);
	ft_strdel(&tmp);
	tmp = *histsave ? made_history((*histsave)[ft_tablen(*histsave) - 1]) : NULL;
	if ((!*histsave || (*histsave && ft_strcmp(tmp, news))) && histsize > 0)
	{
		ft_strdel(&tmp);
		tmp = ft_strjoin("[", news);
		tmp2 = ft_strjoin(tmp, "]");
		ft_malloc_cmd(histsave, tmp2);
		ft_strdel(&tmp2);
	}
	ft_strdel(&tmp);
	return (0);
}

void			history_save(char ***history, char *news, int version, char *s)
{
	static char		**histsave = NULL;
	static char		*path = NULL;
	char			*tmp;

	tmp = NULL;
	if (version == -1)
	{
		int i = 0;
		if (*history)
			while ((*history)[i])
			{
				printf("HISTORY[%d] == %s\n", i, (*history)[i]);
				i++;
			}
		path = ft_strdup(s);
		histsave = ft_tabdup(*history);
	}
	else if (version == 0 && histsave)
		*history = ft_tabdup(histsave);
	else if (version == 1)
		add_memory(news, &histsave);
	else if (version == 2)
	{
		tmp = ft_strjoin(path, "/.101sh_history");
		save_to_file(histsave, tmp);
		ft_tabdel(&histsave);
		ft_strdel(&path);
		ft_strdel(&tmp);
	}
}

static int		occurence(char *little, char *big, char *old)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (big[i] && little[i])
	{
		if (little[i] != big[i])
			return (0);
		i++;
	}
	if (old)
		return (big[i] && ft_strcmp(big, old) ? 1 : 0);
	return (big[i] ? 1 : 0);
}

static int		advanced_history_search(char **history, t_editor **ed)
{
	int			i;
	int			j;
	char		*tmp;
	int			limit;

	j = 0;
	i = 0;
	while (history[i] && j <= (*ed)->hist + 1)
	{
		limit = 0;
		tmp = made_history(history[i]);
		if ((limit = occurence((*ed)->tmp_line, tmp, (*ed)->line)) && j <= (*ed)->hist)
		{
			ft_strdel(&(*ed)->line);
			(*ed)->line = ft_strdup(tmp);
			j++;
		}
		else if (limit && UP_KEY)
		{
			(*ed)->hist = (*ed)->hist + 1;
			return (0);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (0);
}

static int		simple_history_search(t_editor **ed, char **history)
{
	int			i;

	i = 0;
	ft_strdel(&(*ed)->line);
	while (history[i] && i <= (*ed)->hist)
	{
		ft_strdel(&(*ed)->line);
		(*ed)->line = made_history(history[i++]);
	}
	(*ed)->hist = history[i] ? (*ed)->hist + 1 : (*ed)->hist;
	return (0);
}

void			history_get(t_editor **ed)
{
	char		**history;

	history = NULL;
	history_save(&history, NULL, 0, (char *)NULL);
	ft_reverse_tab(&history);
	if (history)
	{
		if ((*ed)->tmp_line)
		{
			advanced_history_search(history, ed);
			!(*ed)->line ? (*ed)->line = ft_strdup((*ed)->tmp_line) : 0;
		}
		else
			simple_history_search(ed, history);
	}
	ft_tabdel(&history);
}
