/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prelexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/14 23:56:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 17:21:06 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	prelex_quotes(char *line, int *index)
{
	char		c;
	int			i;
	int			dbq;

	if (ft_isquote(line[*index]))
	{
		i = 0;
		c = line[*index];
		*index = *index + 1;
		dbq = 0;
		while (line[*index])
		{
			if (line[*index] == '\\' && c != '\'')
				*index = *index + 1;
			else if (c == '"' && line[*index] == '`')
				dbq = dbq == 0 ? 1 : 0;
			else if (line[*index] == c && dbq == 0)
				return (0);
			*index = line[*index] ? *index + 1 : *index;
		}
		if (c == '\'' || c == '`')
			return (c == '\'' ? S_QUOTE : B_QUOTE);
		return (dbq == 0 ? D_QUOTE : DB_QUOTE);
	}
	return (0);
}

static int	orif_and_pipe(int i, char **line)
{
	if (i > 0 && (*line)[i - 1] == '|')
	{
		ft_chardel_at(line, ft_strlen(*line) - 1);
		return (g_prompt = ORIF);
	}
	else
	{
		ft_chardel_at(line, ft_strlen(*line) - 1);
		return (g_prompt = E_PIPE);
	}
}

static int	prelex_bslash(char **line)
{
	(void)line;
	ft_chardel_at(line, ft_strlen(*line) - 1);
	ft_chardel_at(line, ft_strlen(*line) - 1);
	return (g_prompt = BACKSLASH);
}

static void	prelex_cmdsubst(char c, int *sub)
{
	if (c == '(')
		*sub = *sub + 1;
	else if (c == ')' && *sub > 0)
		*sub = *sub - 1;
}

int			prelexer(char **line)
{
	int				i;
	unsigned int	ret;
	int				sub;

	sub = 0;
	ret = 0;
	i = -1;
	while (*line && (*line)[++i])
		if ((*line)[i] == '\\' && (*line)[i + 1] && (*line)[i + 2])
			i++;
		else if ((*line)[i] == '\\' && (*line)[i + 1] && !(*line)[i + 2])
			return (prelex_bslash(line));
		else if ((*line)[i] == '|' && ft_str_isblank(*line + (i + 1)))
			return (orif_and_pipe(i, line));
		else if (i > 0 && (*line)[i - 1] == '&' && (*line)[i] == '&' &&
				ft_str_isblank(*line + (i + 1)))
			return (g_prompt = ANDIF + prelex_norm(line));
		else if ((ret = prelex_quotes(*line, &i)))
			return (g_prompt = ret + prelex_norm(line));
		else if ((*line)[i] == '(' || (*line)[i] == ')')
			prelex_cmdsubst((*line)[i], &sub);
	return (sub >= 1 ? g_prompt = SUBST : 0);
}
