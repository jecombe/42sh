/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cmd_split.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 05:14:23 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 11:28:37 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static size_t	cmd_wordlen(const char *s, size_t i, int size)
{
	size_t		count;

	count = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if ((count > 0 && s[i - 1] == '\n') || (int)count == size)
				return (count);
			count++;
			i++;
		}
	}
	return (count);
}

static char		*cmd_add_prompt(const char *s, int len)
{
	char	tmp[len + 1];
	int		i;

	ft_bzero(&tmp, len);
	i = 0;
	while (i < len)
	{
		tmp[i] = ' ';
		i++;
	}
	return (ft_strjoin(tmp, s));
}

char			**ft_cmd_split(t_shell *ed)
{
	char	**grid;
	size_t	i;
	char	*tmp;
	char	*s;

	grid = NULL;
	if (g_cmd)
	{
		s = cmd_add_prompt(g_cmd, ed->prompt_len);
		i = 0;
		while (s[i])
		{
			tmp = ft_strsub(s, (int)i, cmd_wordlen(s, i, ed->ws.ws_col));
			ft_malloc_cmd(&grid, tmp);
			i += ft_strlen(tmp);
			ft_strdel(&tmp);
		}
	}
	return (grid);
}
