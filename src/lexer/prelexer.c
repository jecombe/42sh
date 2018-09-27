/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prelexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/14 23:56:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 01:39:15 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	prelex_squotes(char *line, char *lst, int *index, char c)
{
	if (line[*index + 1])
	{
		while (line[++(*index)] && line[*index] != c)
		{
			if (!line[*index + 1] && line[(*index)] != c)
			{
				*lst = 0;
				return (S_QUOTE);
			}
		}
	}
	else
	{
		*lst = 0;
		return (S_QUOTE);
	}
	return (PROMPT);
}

static int	prelex_bquotes(char *line, char *lst, int *index, char c)
{
	int				ret;

	ret = 0;
	if (line[*index + 1])
	{
		while (line[++(*index)] && line[*index] != c)
		{
			if (!line[*index + 1] && line[*index] != c)
			{
				ret = *lst;
				*lst = 0;
				return (ret ? DB_QUOTE : B_QUOTE);
			}
		}
	}
	else
	{
		ret = *lst;
		*lst = 0;
		return (ret ? DB_QUOTE : B_QUOTE);
	}
	return (PROMPT);
}

static int	prelex_quotes(char c, int version, char *line, int *index)
{
	static char		lst = 0;
	int				ret;

	if (version == 0)
	{
		if (c == '\'')
			return (prelex_squotes(line, &lst, index, c));
		else if (c == '`')
			return (prelex_bquotes(line, &lst, index, c));
		else if (c == '"')
			lst = lst == '"' ? 0 : '"';
		else if (c == '|' && ft_str_isblank(line + (*index + 1)) && lst == 0)
			return (E_PIPE);
		return (PROMPT);
	}
	ret = lst;
	lst = 0;
	return (ret == '"' ? D_QUOTE : PROMPT);
}

int			prelexer(char *line)
{
	int				i;
	unsigned int	ret;

	ret = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1])
			i++;
		else if (line[i] == '\\' && !line[i + 1])
			return (BACKSLASH);
		else if ((ret = prelex_quotes(line[i], 0, line, &i)))
			return (ret);
		i++;
	}
	return (prelex_quotes(0, 1, NULL, (int*)0));
}
