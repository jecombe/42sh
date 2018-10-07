/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 04:59:26 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 08:32:12 by dzonda      ###    #+. /#+    ###.fr     */
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

char			*made_history(char *str)
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
	char	*s;
	char	*tmp2;
	int		histsize;
	int		histfilesize;

	s = ft_getenv("HISTSIZE", g_set);
	histsize = s && ft_strisdigit(s) ? ft_atoi(s) : 500;
	ft_strdel(&s);
	histfilesize = *histsave ? ft_tablen(*histsave) + 1 : 1;
	while (--histfilesize >= histsize && histfilesize >= 0)
		ft_strdel_in_tab(histsave, 0);
	s = ft_itoa(histfilesize == 500 ? histfilesize : histfilesize + 1);
	add_to_set("HISTFILESIZE", s);
	ft_strdel(&s);
	s = *histsave ? made_history((*histsave)[ft_tablen(*histsave) - 1]) : NULL;
	if ((!*histsave || (*histsave && ft_strcmp(s, news))) && histsize > 0)
	{
		ft_strdel(&s);
		s = ft_strjoin("[", news);
		tmp2 = ft_strjoin(s, "]");
		ft_malloc_cmd(histsave, tmp2);
		ft_strdel(&tmp2);
	}
	ft_strdel(&s);
	return (0);
}

void			history_save(char ***history, char *news, int version, char *s)
{
	static char		**histsave = NULL;
	static char		*path = NULL;
	char			*tmp;
	int				i;

	tmp = NULL;
	i = -1;
	if (version == -1)
	{
		if (*history)
			while ((*history)[++i])
				printf("HISTORY[%d] == %s\n", i, (*history)[i]);
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
