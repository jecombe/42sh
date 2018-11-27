/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   subshell_manager.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/25 07:07:56 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 10:32:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	subshell_bracket(char *cmd, char c)
{
	int		i;
	int		last;

	last = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c && ((i > 0 && cmd[i - 1] != '\\') || i == 0))
			last = i;
		i++;
	}
	return (last);
}

int			recup_inside_subshell(char **cmd, int *j, char **line)
{
	int			i;

	if ((i = subshell_bracket(*cmd + *j + 1, ')')))
	{
		if (i - 1 < 1)
		{
			return (1);
		}
		*line = ft_strsub(*cmd, *j + 1, i);
		*j += i + 1;
		return (1);
	}
	*j = *j + 1;
	return (0);
}

static int	error_sub(char ***cmd, t_bquote **i, int index_tmp)
{
	char		*line;

	line = NULL;
	recup_inside_subshell(&(*cmd)[(*i)->i], &(*i)->j, &line);
	ft_putstr_fd("101sh: syntax error near unexpected token `", 2);
	ft_putstr_fd(line, 2);
	ft_putendl_fd("'", 2);
	(*i)->begin = index_tmp;
	ft_strdel(&line);
	ft_tabdel(cmd);
	add_to_set("?", "258");
	return (1);
}

int			subshell_manager(char ***cmd, t_bquote **i)
{
	char		*line;
	t_prompt	prompt;
	int			index_tmp;

	line = NULL;
	prompt = PROMPT;
	index_tmp = (*i)->begin;
	(*i)->begin = (*i)->j;
	if ((*i)->j != 0 && ((*cmd)[(*i)->i][(*i)->j - 1] == '$'))
	{
		if (dollar_sub(cmd, i, prompt, &index_tmp))
			return (1);
	}
	else if ((*i)->i != 0)
		return (error_sub(cmd, i, index_tmp));
	else
	{
		ft_chardel_at(&(*cmd)[(*i)->i], (*i)->j);
		ft_chardel_at(&(*cmd)[(*i)->i],
				subshell_bracket((*cmd)[(*i)->i] + (*i)->j, ')'));
	}
	(*i)->begin = index_tmp;
	return (0);
}
