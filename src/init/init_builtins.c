/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_builtins.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:57:58 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 02:00:51 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	init_builtins_history_add(char *line, char **buf)
{
	char	*tmp;

	tmp = NULL;
	if (!(*buf))
		*buf = ft_strdup(line);
	else
	{
		if (!(tmp = ft_strjoin(*buf, "\n")))
			return (EXIT_FAILURE);
		ft_strdel(buf);
		if (!((*buf) = ft_strjoin(tmp, line)))
			return (EXIT_FAILURE);
		ft_strdel(&tmp);
	}
	if (((*buf)[ft_strlen(*buf) - 1]) == ']')
	{
		if (!(tmp = ft_strsub(*buf, 1, ft_strlen(*buf) - 2)))
			return (EXIT_FAILURE);
		history_add(tmp);
		ft_strdel(&tmp);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int	init_builtins_history_read(int fd, int *i)
{
	char	*str;
	char	*buf;

	str = NULL;
	buf = NULL;
	while (get_next_line(fd, &str))
	{
		if (!(init_builtins_history_add(str, &buf)))
		{
			ft_strdel(&buf);
			(*i)++;
		}
		ft_strdel(&str);
	}
	ft_strdel(&str);
	ft_strdel(&buf);
	return (EXIT_SUCCESS);
}

static int	init_builtins_history(const char *path)
{
	char	*str;
	int		fd;
	int		i;

	str = NULL;
	fd = -1;
	i = 0;
	if (!(str = ft_strjoin(path, "/.101sh_history")))
		return (EXIT_FAILURE);
	if ((fd = open(str, O_RDONLY)) == -1)
		return (EXIT_FAILURE);
	init_builtins_history_read(fd, &i);
	add_to_set("HISTSIZE", "500");
	add_to_set("HISTFILE", str);
	ft_strdel(&str);
	if (!(str = ft_itoa(i)))
		return (EXIT_FAILURE);
	add_to_set("HISTFILESIZE", str);
	ft_strdel(&str);
	return (close(fd) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

int			init_builtins(const char *path)
{
	t_hashtable		*hashtable;
	t_history		*history;
	int				i;

	hashtable = NULL;
	history = NULL;
	i = -1;
	if (!(hashtable = (t_hashtable *)malloc(sizeof(t_hashtable) * MAX_HASH)))
		return (EXIT_FAILURE);
	while (++i < MAX_HASH)
	{
		hashtable[i].key = 0;
		hashtable[i].hashcase = NULL;
	}
	ft_save_hash(&hashtable);
	if (!(history = (t_history *)malloc(sizeof(t_history))))
		return (EXIT_FAILURE);
	history->cmd = NULL;
	history_save(&history);
	init_builtins_history(path);
	history_get(NULL, 0);
	return (EXIT_SUCCESS);
}
