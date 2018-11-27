/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 04:59:26 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 03:45:37 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	save_to_file(char **histsave, char *path)
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

static char	*made_history(char *str)
{
	char		*ret;
	int			i;
	int			j;

	j = 0;
	i = 0;
	ret = NULL;
	if (str && str[1] && str[2])
	{
		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
			return (NULL);
		while (str[++i] && str[i + 1])
		{
			if (i != 0 && str[i + 1])
				ret[j++] = str[i];
		}
		ret[j] = '\0';
	}
	return (ret);
}

static void	add_memory(char *news, char ***histsave)
{
	char	*s;
	char	tmp[ft_strlen(news) + 2];
	int		histsize;
	int		histfilesize;

	s = ft_getenv("HISTSIZE", g_set);
	histsize = s && ft_strisdigit(s) ? ft_atoi(s) : 500;
	ft_strdel(&s);
	s = *histsave ? made_history((*histsave)[ft_tablen(*histsave) - 1]) : NULL;
	ft_strcpy(tmp, "[");
	ft_strncat(tmp, news, ft_strlen(news) - 1);
	if ((!*histsave || ft_strcmp(s, tmp + 1)) && histsize > 0)
	{
		ft_strdel(&s);
		histfilesize = *histsave ? ft_tablen(*histsave) + 1 : 1;
		while (--histfilesize >= histsize && histfilesize >= 0)
			ft_strdel_in_tab(histsave, 0);
		s = ft_itoa(histfilesize == 500 ? histfilesize : histfilesize + 1);
		add_to_set("HISTFILESIZE", s);
		ft_strdel(&s);
		ft_malloc_cmd(histsave, strcat(tmp, "]"));
		s = ft_itoa(histfilesize == 500 ? histfilesize : histfilesize + 1);
		add_to_set("HISTFILESIZE", s);
	}
	ft_strdel(&s);
}

void		history_save(char ***history, char *news, int version, char *s)
{
	static char		**histsave = NULL;
	static char		*path = NULL;
	char			*tmp;

	if (version == -1)
	{
		path = ft_strdup(s);
		histsave = ft_tabdup(*history);
	}
	else if (version == 0 && histsave)
		*history = ft_tabdup(histsave);
	else if (version == 1 && news[1])
	{
		add_memory(news, &histsave);
	}
	else if (version == 2)
	{
		tmp = ft_strjoin(path, "/.101sh_history");
		save_to_file(histsave, tmp);
		ft_tabdel(&histsave);
		ft_strdel(&path);
		ft_strdel(&tmp);
	}
}
