/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bquote_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 07:06:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 11:51:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

static int	add_and_del_tab(char ***ret, char ***to_copy)
{
	int		i;

	i = 0;
	if (*to_copy)
	{
		while ((*to_copy)[i])
			ft_malloc_cmd(ret, (*to_copy)[i++]);
		ft_tabdel(&(*to_copy));
		return (1);
	}
	return (0);
}

char		**first_copy(char **cmd, t_bquote *index, char *in_bquote, int *ok)
{
	char	**ret;
	char	**prev_cmd;
	char	*ifs;
	char	**result_bquote;

	ret = NULL;
	if (!(ifs = ft_getenv("IFS", g_set)))
		ifs = ft_strdup("\n \t");
	prev_cmd = search_prev(cmd, index->i);
	if (index->dquote)
	{
		if (ft_malloc_cmd(&result_bquote, in_bquote))
			return (NULL);
	}
	else
		result_bquote = ft_split_bquote(in_bquote, ifs);
	ifs ? ft_strdel(&ifs) : 0;
	add_before_bquote(cmd[index->i], index->begin, &result_bquote);
	add_and_del_tab(&ret, &prev_cmd);
	*ok = add_and_del_tab(&ret, &result_bquote);
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

static char		**search_next(char **cmd, int after)
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

int			last_copy(char ***begin_copy, char **cmd, t_bquote *index, int ok)
{
	int			i;
	char		**next_cmd;

	i = 0;
	next_cmd = NULL;
	add_after_bquote(cmd[index->i], index->j + 1, begin_copy, ok);
	if ((next_cmd = search_next(cmd, index->i + 1)))
	{
		while (next_cmd[i])
		{
			ft_malloc_cmd(begin_copy, next_cmd[i]);
			i++;
		}
		ft_tabdel(&next_cmd);
	}
	return (0);
}
