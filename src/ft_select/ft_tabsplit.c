/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 03:31:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 04:45:41 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

static int			issep(const char *s, int i)
{
	if (ft_isseparator(s[i]) && (i == 0 || (i > 0 && s[i - 1] != '\\')))
		return (1);
	return (0);
}

static size_t		wordlen(const char *s, size_t index, int *cursor_pos)
{
	int i = index;
	size_t	count;
	char	c;

	(void)cursor_pos;
	c = s[i];
	count = 0;
	if (ft_isseparator(c))
		while (s[i] == c)
		{
			count++;
			i++;
		}
	else if (ft_isblank(c))
	{
		while (ft_isblank(s[i]) && s[i] && !(i + 1== *cursor_pos))
//		while (ft_isblank(s[i]) && s[i])
		{
			printf("++\n");
			i++;
			count++;
		}
		if (ft_isblank(s[i]))
			printf("IS_BLANK I == %d COUNT == %ld CURSOR == %d\n\n", i, count, *cursor_pos);
//		count += i == *cursor_pos + 1 && ft_isblank(s[i]) ? 1 : 0;
		if ((i == *cursor_pos + 1 && ft_isblank(s[i])) || (i == *cursor_pos && ft_isblank(s[i])))
		{
			printf("+1 i == %d CURSOR == %d COUNT == %ld s[i] == |%c|\n", i, *cursor_pos, count, s[i]);
			count++;
		}
//		else if (i == *cursor_pos && !ft_isblank(s[i]))
//		{
//			printf("-1 i == %d CURSOR == %d, COUNT == %ld s[i] == |%c|\n", i, *cursor_pos, count, s[i]);
//		//	count--;
//		}
	}
	else if (ft_isprint(c) && !ft_isblank(c))
		while (ft_isprint(s[i]) && !ft_isblank(s[i]) && s[i] && !issep(s, i))
		{
			i++;
			count++;
		}
	return (count);
}

char				**ft_tabsplit(const char *s, int cursor_pos)
{
	char	**tablo;
	size_t	i;
	char	*tmp;
	char	*tmp2 = NULL;
	int		set_cursor[2];
		int u = -1;

	set_cursor[1] = cursor_pos;
	set_cursor[0] = cursor_pos;
	i = 0;
	tablo = NULL;
	if (s)
	{
		while (s[i] != '\0')
		{
			u = -1;
			tmp = ft_strsub(s, ((int)i), wordlen(s, i, &set_cursor[0]));
			//printf("TMP[i] == |%s|\n", tmp);
			i += wordlen(s, i, &set_cursor[1]);
			if ((!tablo || cursor_pos == 2147483646) && !(i >= (size_t)cursor_pos))
			{
			printf("00I == %d CURSOR == %d\n", (int)i, cursor_pos);
				ft_malloc_cmd(&tablo, tmp);
				cursor_pos = cursor_pos == 2147483646 ? 2147483645 : cursor_pos;
			}
			else if (i >= (size_t)cursor_pos)
			{
			printf("11I == %d CURSOR == %d\n", (int)i, cursor_pos);
				if (!tablo)
					ft_malloc_cmd(&tablo, "");
				ft_malloc_cmd(&tablo, tmp);
				cursor_pos = 2147483646;

			}
			else
			{
			printf("22I == %d CURSOR == %d\n", (int)i, cursor_pos);
				tmp2 = ft_strjoin(tablo[ft_tablen(tablo) - 1], tmp);
				ft_strdel(&tablo[ft_tablen(tablo) - 1]);
				tablo[ft_tablen(tablo)] = ft_strdup(tmp2);
				if (cursor_pos == (int)i + 1 && ft_isblank(s[i]))
				{
			printf("-1 i == %ld CURSOR == %d s[i] == |%c|\n", i, cursor_pos ,s[i]);
					i++;
				}
				ft_strdel(&tmp2);
			}
		while (tablo[++u])
			printf("TABLO[%d] == |%s|\n", u, tablo[u]);
			ft_strdel(&tmp);
		}
		printf("\n");
	}
//	sleep(2);
	return (tablo);
}
