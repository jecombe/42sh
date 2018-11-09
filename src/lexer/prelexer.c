/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prelexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/14 23:56:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 07:51:37 by gmadec      ###    #+. /#+    ###.fr     */
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

int			prelexer(char **line)
{
	int				i;
	unsigned int	ret;

	ret = 0;
	i = -1;
	while (*line && (*line)[++i])
		if ((*line)[i] == '\\' && (*line)[i + 1] && (*line)[i + 2])
			i++;
		else if ((*line)[i] == '\\' && (*line)[i + 1] && !(*line)[i + 2])
		{
			ft_chardel_at(line, ft_strlen(*line) - 1);
			return (g_prompt = BACKSLASH);
		}
		else if ((*line)[i] == '|' && ft_str_isblank(*line + (i + 1)))
		{
			ft_chardel_at(line, ft_strlen(*line) - 1);
			return (g_prompt = E_PIPE);
		}
		else if ((ret = prelex_quotes(*line, &i)))
		{
			ft_chardel_at(line, ft_strlen(*line) - 1);
			return (g_prompt = ret);
		}
	return (0);
}
