/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bquote_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 07:06:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 07:08:59 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int			add_after_bquote(char *cmd, int j_index, char ***tablo, int ok)
{
	char		*tmp;
	char		*tmp2;
	int			tab_index;

	tab_index = 0;
	tmp = NULL;
	if (j_index < ft_strlen(cmd))
	{
		tmp = ft_strsub(cmd, j_index, ft_strlen(cmd) - j_index);
		if (*tablo && ok)
		{
			tab_index = ft_tablen(*tablo) - 1;
			tmp2 = ft_strjoin((*tablo)[tab_index], tmp);
			tmp2 = ft_strjoin((*tablo)[tab_index], tmp);
			ft_strdel(&(*tablo)[tab_index]);
			(*tablo)[tab_index] = ft_strdup(tmp2);
		}
		else
		{
			ft_malloc_cmd(tablo, tmp);
		}
		ft_strdel(&tmp);
	}
//	else
//		printf("PAS DE ADD AFTER QUOTE\n");
	return (0);
}

int			add_before_bquote(char *line, int begin, char ***cmd)
{
	char		*tmp;
	char		*before_bquote;
	int			i;

	before_bquote = NULL;
	i = 0;
	tmp = NULL;
	if (begin > 0)
	{
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
//	else
//		printf("PAS DE ADD BEFORE QUOTE\n");
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

char		**first_copy(char **cmd, int i_index, char *in_bquote, int begin, int *ok)
{
	char	**ret;
	char	**prev_cmd;
	char	*ifs;
	char	**result_bquote;
	int		i;
	char *tmp = NULL;

	i = 0;
	ret = NULL;
	if (!(ifs = ft_getenv("IFS", g_set)))
		ifs = ft_strdup("\n \t");
//	printf("IN_BQUOTE == %s\n", in_bquote);
	prev_cmd = search_prev(cmd, i_index);
	result_bquote = ft_split_bquote(in_bquote, ifs);
	add_before_bquote(cmd[i_index], begin, &result_bquote);
	if (prev_cmd)
		while (prev_cmd[i])
		{
//			printf("PREV_CMD[%d] == %s\n", i, prev_cmd[i]);
			ft_malloc_cmd(&ret, prev_cmd[i++]);
		}
	i = 0;
	if (result_bquote)
	{
		*ok = 1;
		while (result_bquote[i])
		{
//			if (tmp)
//				tmp = ft_strjoin(tmp, result_bquote[i]);
//			else
//				tmp = ft_strdup(result_bquote[i]);
//			printf("RESULT_BQUOTE[%d] == %s\n", i, result_bquote[i]);
			ft_malloc_cmd(&ret, result_bquote[i++]);
//			i++;
		}
	}
//	ft_malloc_cmd(&ret, tmp);
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

int			last_copy(char ***begin_copy, char **cmd, int i_index, int j_index, int ok)
{
	int			i;
	char		**next_cmd;

	i = 0;
	next_cmd = NULL;
	add_after_bquote(cmd[i_index], j_index + 1, begin_copy, ok);
	next_cmd = search_next(cmd, i_index + 1);
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

int			ft_bquote_replace(char ***cmd, char *in_bquote, int *i_index, int *j_index, int begin)
{
	char		**next_cmd;
	int			i = 0;
	char		**begin_copy;
	int			tmp_i;
	int			tmp_j;

	tmp_i = 0;
	tmp_j = 0;
	begin_copy = first_copy(*cmd, *i_index, in_bquote, begin, &i);
	search_index(begin_copy, &tmp_i, &tmp_j);
//	printf("TMP_I == %d, TMP_J == %d\n", tmp_i, tmp_j);
	last_copy(&begin_copy, *cmd, *i_index, *j_index, i);
	replace_cmd(begin_copy, cmd);
	if (*cmd);
//		while ((*cmd)[i])
//		{
//			printf("CMD[%d] == %s\n", i, (*cmd)[i]);
//			i++;
//		}
	else
	{
		*i_index = tmp_i;
		*j_index = tmp_j;
//		printf("I == %d, J == %d\n", tmp_i, tmp_j);
		return (1);
	}
	*i_index = tmp_i;
	*j_index = tmp_j;
	return (0);
}//ATTRIBUER LA BONNE VALEUR A J_INDEX

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

	prompt = PROMPT;
	if ((line = recup_inside_bquote((*cmd)[*i_index], begin, *j_index)))
	{
		fd = open(".tmp_file", O_CREAT | O_TRUNC , 0666);
		heart_of_101sh(line, &prompt, fd);
		ft_strdel(&line);
		close(fd);
		line = get_tmp_file((*cmd)[*i_index], begin, *j_index);
	}
	if (ft_bquote_replace(&(*cmd), line, i_index, j_index, begin))
		return (1);
	return (0);
}
