
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

static int	init_builtins_history(const char *path)
{
	char	*str;
	char	*buf;
	int		fd;

	str = NULL;
	buf = NULL;
	fd = -1;
	if (!(str = ft_strjoin(path, "/.101sh_history")))
		return (EXIT_FAILURE);
	if (((fd = open(str, O_RDONLY))) == -1)
		return (EXIT_FAILURE);
	ft_strdel(&str);
	while (get_next_line(fd, &str))
	{
		if (!(init_builtins_history_add(str, &buf)))
			ft_strdel(&buf);
		ft_strdel(&str);
	}
	ft_strdel(&str);
	ft_strdel(&buf);
	if ((close(fd)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}
