/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dollar_sub.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/25 16:23:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 10:34:55 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	init_dollar_sub(char ***cmd, t_bquote **i, t_prompt *prompt,
		int *index_tmp)
{
	ft_chardel_at(&(*cmd)[(*i)->i], (*i)->j - 1);
	(*i)->j = (*i)->j - 1;
	*prompt = PROMPT;
	*index_tmp = (*i)->begin;
	(*i)->begin = (*i)->j;
}

int			dollar_sub(char ***cmd, t_bquote **i, t_prompt prompt,
		int *index_tmp)
{
	char		*tmp;
	char		*line;

	line = NULL;
	init_dollar_sub(cmd, i, &prompt, index_tmp);
	if (recup_inside_subshell(&(*cmd)[(*i)->i], &(*i)->j, &line))
	{
		tmp = ft_strdup(line);
		if ((prompt = prelexer(&tmp)) != PROMPT && err_bquote_unmatched(prompt))
		{
			ft_strdel(&tmp);
			ft_strdel(&line);
			(*i)->begin = *index_tmp;
			return (1);
		}
		heart_of_101sh(line, 3);
		ft_strdel(&tmp);
		ft_strdel(&line);
		line = get_tmp_file();
	}
	if (ft_bquote_replace(&(*cmd), &line, i) &&
			(((*i)->begin = *index_tmp) || 1))
		return (1);
	return (0);
}
