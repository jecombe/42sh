/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 03:31:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 06:26:11 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int			issep(const char *s, int i)
{
	if (ft_isseparator(s[i]) && (i == 0 || (i > 0 && s[i - 1] != '\\')))
		return (1);
	return (0);
}

static size_t		wordlen(const char *s, size_t index, int *find, int *cursor)
{
	int i = index;
	size_t	count;
	char	c;

	c = s[i];
	count = 0;
	if (ft_isseparator(c))
	{
		if (s[i] == c && i != *cursor)
		{
			while (s[i] == c)
			{
				if (*find == 3)
				{
					*find = 2;
					*cursor = -1;
					return (count);
				}
				if (i + 1 == *cursor && *find != -1)
				{
					*find = 3;
					*cursor += 1;
				}
				i++;
				count++;
			}
		}
		else if (i == *cursor && *find != -1)
		{
			*cursor += 1;
			if (*find != -1)
				*find = 3;
		}
	}
	else if (ft_isblank(c))
	{
		if (ft_isblank(s[i])  && i != *cursor)
		{
			while (ft_isblank(s[i]) && s[i] && i != *cursor)
			{
				if (i == *cursor && *find != -1)
				{
					*find = 2;
					*cursor = -1;
					break ;
				}
				i++;
				count++;
			}
		}
		else if (i == *cursor)
		{
			*cursor = -1;
			if (*find != -1)
				*find = 2;
		}
	}
	else if (ft_isprint(c) && !ft_isblank(c))
		while (ft_isprint(s[i]) && !ft_isblank(s[i]) && s[i] && !issep(s, i))
		{
			if ((i == *cursor || i + 1 == *cursor) && *find != -1)
			{
				*find = 1;
				*cursor = -1;
			}
			i++;
			count++;
		}
	return (count);
}

char				**ft_tabsplit(const char *s, int cursor_pos)
{
	char	**tablo;
	size_t	i;
	int		i_tmp;
	char	*tmp;
	char	*tmp2;
	int		find_cursor;

	find_cursor = 0;
	i = 0;
	i_tmp = 0;
	tablo = NULL;
	if (s)
	{
		while (s[i])
		{
			i_tmp = wordlen(s, i, &find_cursor, &cursor_pos);
			tmp = ft_strsub(s, ((int)i), i_tmp);
			i += i_tmp;
			if (find_cursor == 1)
			{
				if (!tablo)
					ft_malloc_cmd(&tablo, "");
				if (!tablo[1])
					ft_malloc_cmd(&tablo, tmp);
				else
				{
					i_tmp = ft_tablen(tablo) - 1;
					tmp2 = ft_strjoin(tablo[i_tmp], tmp);
					ft_strdel(&tablo[i_tmp]);
					tablo[i_tmp] = ft_strdup(tmp2);
					ft_strdel(&tmp2);
				}
				ft_malloc_cmd(&tablo, "");
				find_cursor = -1;
			}
			else if (find_cursor == 2)
			{
				if (!tablo)
					ft_malloc_cmd(&tablo, tmp);
				else
				{
					i_tmp = ft_tablen(tablo) - 1;
					tmp2 = ft_strjoin(tablo[i_tmp], tmp);
					ft_strdel(&tablo[i_tmp]);
					tablo[i_tmp] = ft_strdup(tmp2);
					ft_strdel(&tmp2);
				}
				if (!tablo[1])
					ft_malloc_cmd(&tablo, "");
				ft_malloc_cmd(&tablo, "");
				find_cursor = -1;
			}
			else
			{
				if (!tablo)
					ft_malloc_cmd(&tablo, tmp);
				else
				{
					i_tmp = ft_tablen(tablo) - 1;
					tmp2 = ft_strjoin(tablo[i_tmp], tmp);
					ft_strdel(&tablo[i_tmp]);
					tablo[i_tmp] = ft_strdup(tmp2);
					ft_strdel(&tmp2);
				}
			}
			ft_strdel(&tmp);
		}
		!tablo ? ft_malloc_cmd(&tablo, "") : 0;
		!tablo[1] ? ft_malloc_cmd(&tablo, "") : 0;
		!tablo[2] ? ft_malloc_cmd(&tablo, "") : 0;
	}
	return (tablo);
}
