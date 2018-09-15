/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bquote_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 07:06:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 05:18:00 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	replace_cmd(char **to_copy, char ***to_past)
{
	int			i;

	i = 0;
	if (*to_past)
	ft_tabdel(to_past);
	if (to_copy)
		while (to_copy[i])
			ft_malloc_cmd(to_past, to_copy[i++]);
	return (0);
}

static int	ft_bquote_replace(char ***cmd, char **in_bquote, t_bquote **index)
{
	int			i = 0;
	char		**begin_copy;
	int			tmp_i;
	int			tmp_j;

	tmp_i = 0;
	tmp_j = 0;
	begin_copy = first_copy(*cmd, *index, *in_bquote, &i);
	*in_bquote ? ft_strdel (in_bquote) : 0;
	search_index(begin_copy, &tmp_i, &tmp_j);
	last_copy(&begin_copy, *cmd, *index, i);
	replace_cmd(begin_copy, cmd);
	if (begin_copy)
		ft_tabdel(&begin_copy);
	(*index)->i = tmp_i;
	(*index)->j = tmp_j;
	return (*cmd ? 0 : 1);
}

static char	*recup_inside_bquote(char *cmd, int begin, int j_index)
{
	char		*ret;

	ret = NULL;
	if (begin + 1 < j_index)
		ret = ft_strsub(cmd, begin + 1, j_index - (begin + 1));
	return (ret);
}

static char	*get_tmp_file(char *cmd, int begin, int j_index)
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

int			bquote_manager(char ***cmd, t_bquote **i)
{
	int			fd;
	char		*line;
	e_prompt	prompt;

	prompt = PROMPT;
	if ((line = recup_inside_bquote((*cmd)[(*i)->i], (*i)->begin, (*i)->j)))
	{
		if (prelexer(line) != PROMPT)
			return (1);
		else
			printf("QUOTES VALIDES\n");
		fd = 3;
		//fd = open(".tmp_file", O_CREAT | O_TRUNC , 0666);
		heart_of_101sh(line, fd);
//		ft_strdel(&line);
		//close(fd);
//	fflush(NULL);
		line = get_tmp_file((*cmd)[(*i)->i], (*i)->begin, (*i)->j);
	}
	if (ft_bquote_replace(&(*cmd), &line, i))
		return (1);
	return (0);
}
