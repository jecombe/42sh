/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bquote_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 07:06:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 15:14:30 by gmadec      ###    #+. /#+    ###.fr     */
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

int			ft_bquote_replace(char ***cmd, char **in_bquote, t_bquote **index)
{
	int			i;
	char		**begin_copy;
	int			tmp_i;
	int			tmp_j;

	i = 0;
	tmp_i = 0;
	tmp_j = 0;
	begin_copy = first_copy(*cmd, *index, *in_bquote, &i);
	*in_bquote ? ft_strdel(in_bquote) : 0;
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

char		*get_tmp_file(void)
{
	char		*ret;
	char		*line;
	int			fd;

	ret = NULL;
	line = NULL;
	if (g_error_bquote == 0 && access(".tmp_file", 0) != -1)
	{
		fd = open(".tmp_file", O_RDONLY);
		while (fd && get_next_line(fd, &line) > 0 && g_interupt == 0)
		{
			ret = ret ? ft_strjoin_free(ret, "\n") : NULL;
			ret = ft_strjoin_free(ret, line);
			ft_strdel(&line);
		}
		ft_strdel(&line);
		g_interupt == 1 ? ft_strdel(&ret) : 0;
		fd > -1 ? close(fd) : 0;
		fd > -1 ? unlink(".tmp_file") : 0;
	}
	return (ret);
}

int			bquote_manager(char ***cmd, t_bquote **i)
{
	char		*line;
	char		*tmp;
	t_prompt	prompt;

	prompt = PROMPT;
	line = NULL;
	if ((line = recup_inside_bquote((*cmd)[(*i)->i], (*i)->begin, (*i)->j)))
	{
		tmp = ft_strdup(line);
		if ((prompt = prelexer(&tmp)) != PROMPT)
		{
			ft_strdel(&tmp);
			ft_strdel(&line);
			return (err_bquote_unmatched(prompt));
		}
		ft_strdel(&tmp);
		heart_of_101sh(line, 3);
		ft_strdel(&line);
		line = get_tmp_file();
	}
	if (ft_bquote_replace(&(*cmd), &line, i))
		return (1);
	ft_strdel(&line);
	return (0);
}
