/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prelexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/14 23:56:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 05:42:24 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	prelex_search_quotes(char c, char *lst, char *line, int *index)
{
	int				ret;

	ret = 0;
	if (c == '\'')
	{
		while (line[++(*index)])
		{
			if (!line[*index + 1] && line[(*index)] != c)
			{
				*lst = 0;
	printf("0RET == S_QUOTE\n");
				return (S_QUOTE);
			}
		}
	}
	else if (c == '`')
	{
		while (line[++(*index)])
		{
			if (!line[*index + 1] && line[*index] != c)
			{
				ret = *lst;
				*lst = 0;
	printf("1RET == %d\n", ret);
				return (ret ? DB_QUOTE : B_QUOTE);
			}
		}
	}
	else if (c == '"')
		*lst = *lst == '"' ? 0 : '"';
	return (PROMPT);
}

static int	prelex_quotes(char c, int version, char *line, int *index)
{
	static char		lst = 0;
	int				ret;

	if (version == 0)
		return (prelex_search_quotes(c, &lst, line, index));
	ret = lst;
	lst = 0;
	printf("2RET == %d\n", ret);
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
		else if ((line[i] == '\\' || line[i] == '|') && !line[i + 1])
		{
			printf("RETURN %d\n", line[i]);
			return (line[i] == '\\' ? BACKSLASH : E_PIPE);
		}
		else if (line[i] == '\'' || line[i] == '"' || line[i] == '`')
		{
			if ((ret = prelex_quotes(line[i], 0, line, &i)))
				return (ret);
		}
		i++;
	}
	return (prelex_quotes(0, 1, NULL, (int*)0));
}
