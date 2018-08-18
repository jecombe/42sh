/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bquote_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 07:06:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/18 19:53:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int			add_after_bquote(char *cmd, int j_index, char ***tablo, int last)
{
	char		*tmp;
	char		*tmp2;
	int			tab_index;

	tab_index = 0;
	tmp = NULL;
	if (j_index < ft_strlen(cmd))
	{
		tmp = ft_strsub(cmd, j_index, ft_strlen(cmd) - j_index);
		if (*tablo && last)
		{
			tab_index = ft_tablen(*tablo) - 1;
			tmp2 = ft_strjoin((*tablo)[tab_index], tmp);
			tmp2 = ft_strjoin((*tablo)[tab_index], tmp);
			ft_strdel(&(*tablo)[tab_index]);
			(*tablo)[tab_index] = ft_strdup(tmp2);
		}
		else
			ft_malloc_cmd(tablo, tmp);
		ft_strdel(&tmp);
	}
	return (0);
}

int			add_before_bquote(char *line, int begin, char ***cmd, int *last)
{
	char		*tmp;
	char		*before_bquote;
	int			i;

	before_bquote = NULL;
	i = 0;
	tmp = NULL;
	if (begin > 0)
	{
		*last = 1;
		before_bquote = ft_strsub(line, 0, begin);
		if (*cmd)
		{
			tmp = ft_strjoin(before_bquote, (*cmd)[0]);
			ft_strdel(&(*cmd)[0]);
			(*cmd)[0] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else
			ft_malloc_cmd(cmd, before_bquote);
		ft_strdel(&before_bquote);
	}
	return (0);
}

char		**search_prev(char **cmd, int i_max)
{
	int			i;
	char		**ret;

	ret = NULL;
	i = 0;
	while (i < i_max)
	{
		if (ft_malloc_cmd(&ret, cmd[i]))
			return (NULL);
		i++;
	}
	return (ret);
}

char		**first_copy(char **cmd, char *in_bquote, int *index[3], int *last)
{
	char	**ret;
	char	**prev_cmd;
	char	*ifs;
	char	**result_bquote;
	int		i;

	i = 0;
	ret = NULL;
	ifs = ft_strdup("s");
	prev_cmd = search_prev(cmd, *index[0]);
	if ((result_bquote = ft_split_bquote(in_bquote, ifs)))
		*last = 1;
	add_before_bquote(cmd[*index[0]], *index[2], &result_bquote, last);
	if (prev_cmd)
		while (prev_cmd[i])
			ft_malloc_cmd(&ret, prev_cmd[i++]);
	i = 0;
	if (result_bquote)
		while (result_bquote[i])
			ft_malloc_cmd(&ret, result_bquote[i++]);
	return (ret);
}

void		search_index(char **begin_copy, int *i, int *j)
{
	if (begin_copy)
	{
		while (begin_copy[*i])
		{
			*j = 0;
			while (begin_copy[*i][*j])
				*j = *j + 1;
			*i = *i + 1;
		}
		*i = *i - 1;
	}
}

char		**search_next(char **cmd, int after)
{
	char		**ret;

	ret = NULL;
	while (cmd[after])
	{
		ft_malloc_cmd(&ret, cmd[after]);
		after++;
	}
	return (ret);
}

int			last_copy(char ***begin_copy, char **cmd, int *index[3], int last)
{
	int			i;
	char		**next_cmd;

	i = 0;
	next_cmd = NULL;
	add_after_bquote(cmd[*index[0]], *index[1] + 1, begin_copy, last);
	next_cmd = search_next(cmd, *index[0] + 1);
	if (next_cmd)
		while (next_cmd[i])
		{
			ft_malloc_cmd(begin_copy, next_cmd[i]);
			i++;
		}
	return (0);
}

int			replace_cmd(char **to_copy, char ***to_past)
{
	int			i;

	i = 0;
	ft_tabdel(to_past);
	if (to_copy)
		while (to_copy[i])
		{
			ft_malloc_cmd(to_past, to_copy[i]);
			i++;
		}
	return (0);
}

int			ft_bquote_replace(char ***cmd, char *in_bquote, int *index[3])
{
	char		**next_cmd;
	int			for_last;
	char		**begin_copy;
	int			tmp_i;
	int			tmp_j;

	for_last = 0;
	tmp_i = 0;
	tmp_j = 0;
	begin_copy = first_copy(*cmd, in_bquote, index, &for_last);
	search_index(begin_copy, &tmp_i, &tmp_j);
	last_copy(&begin_copy, *cmd, index, for_last);
	replace_cmd(begin_copy, cmd);
	*index[0] = tmp_i;
	*index[1] = tmp_j;
	return (!(*cmd) ? 1 : 0);
}

char		*recup_inside_bquote(char *cmd, int begin, int j_index)
{
	char		*ret;

	ret = NULL;
	if (begin + 1 < j_index)
		ret = ft_strsub(cmd, begin + 1, j_index - (begin + 1));
	return (ret);
}

char		*get_tmp_file(char *cmd, int begin, int j_index)
{
	char		*ret;
	char		*tmp;
	char		*line;
	int			fd;

	fd = open(".tmp_file", O_CREAT, O_RDONLY);
	ret = NULL;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ret)
		{
			tmp = ft_strjoin(ret, "\n");
			ft_strdel(&ret);
			ret = ft_strjoin(tmp, line);
			ft_strdel(&tmp);
		}
		else
			ret = ft_strdup(line);
		ft_strdel(&line);
	}
	close(fd);
	return (ret);
}

int			bquote_manager(char ***cmd, int *j_index, int *i_index, int begin)
{
	int			fd;
	char		*line = NULL;
	e_prompt	prompt;
	int			*index[3];

	index[0] = i_index;
	index[1] = j_index;
	index[2] = &begin;
	prompt = PROMPT;
	if ((line = recup_inside_bquote((*cmd)[*i_index], begin, *j_index)))
	{
		fd = open(".tmp_file", O_CREAT | O_TRUNC , 0644);
		heart_of_101sh(line, &prompt, fd);
		ft_strdel(&line);
		close(fd);
		line = get_tmp_file((*cmd)[*i_index], begin, *j_index);
	}
	if (ft_bquote_replace(&(*cmd), line, index))
		return (1);
	return (0);
}
