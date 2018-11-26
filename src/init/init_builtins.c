/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_builtins.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:57:58 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 08:06:05 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	add_multiline(char **ret, char *news, char ***get_hist)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("\n", news);
	tmp2 = ft_strjoin(*ret, tmp);
	ft_strdel(ret);
	*ret = ft_strdup(tmp2);
	if (news && ft_strlen(news) > 0 && news[ft_strlen(news) - 1] == ']')
	{
		ft_malloc_cmd(get_hist, *ret);
		ft_strdel(ret);
	}
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (0);
}

static int	add_hist_to_memory(char **tmp, char *path)
{
	char			**get_hist;
	int				i;
	char			*str;

	i = -1;
	str = NULL;
	get_hist = NULL;
	if (tmp)
		while (tmp[++i])
		{
			if (!str && tmp[i][0] == '[')
			{
				if (tmp[i][ft_strlen(tmp[i]) - 1] == ']')
					ft_malloc_cmd(&get_hist, tmp[i]);
				else
					str = ft_strdup(tmp[i]);
			}
			else if (str)
				add_multiline(&str, tmp[i], &get_hist);
		}
	ft_strdel(&str);
	history_save(&get_hist, NULL, -1, path);
	ft_tabdel(&get_hist);
	return (0);
}

static int	init_builtins_history_read(int fd, int *i, char *path)
{
	char	*str;
	char	**tmp;

	str = NULL;
	tmp = NULL;
	while (get_next_line(fd, &str))
	{
		if (ft_malloc_cmd(&tmp, str))
			return (EXIT_FAILURE);
		(*i)++;
		ft_strdel(&str);
	}
	add_hist_to_memory(tmp, path);
	ft_tabdel(&tmp);
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
	init_builtins_history_read(fd, &i, (char *)path);
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
	int				i;

	hashtable = NULL;
	i = -1;
	if (!(hashtable = (t_hashtable *)malloc(sizeof(t_hashtable) * MAX_HASH)))
		return (EXIT_FAILURE);
	while (++i < MAX_HASH)
	{
		hashtable[i].key = 0;
		hashtable[i].hashcase = NULL;
	}
	ft_save_hash(&hashtable);
	init_builtins_history(path);
	return (EXIT_SUCCESS);
}
