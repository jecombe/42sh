/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 03:31:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 10:34:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	ft_find_word(char ***tablo, char *tmp, int *find_cursor, int i_tmp)
{
	char *tmp2;

	if (!*tablo)
		ft_malloc_cmd(tablo, "");
	if (!(*tablo)[1])
		ft_malloc_cmd(tablo, tmp);
	else
	{
		i_tmp = ft_tablen(*tablo) - 1;
		tmp2 = ft_strjoin((*tablo)[i_tmp], tmp);
		ft_strdel(&(*tablo)[i_tmp]);
		(*tablo)[i_tmp] = ft_strdup(tmp2);
		ft_strdel(&tmp2);
	}
	ft_malloc_cmd(tablo, "");
	*find_cursor = -1;
}

static void	ft_find_space(char ***tablo, char *tmp, int *find_cursor, int i_tmp)
{
	char *tmp2;

	if (!*tablo)
		ft_malloc_cmd(tablo, tmp);
	else
	{
		i_tmp = ft_tablen(*tablo) - 1;
		tmp2 = ft_strjoin((*tablo)[i_tmp], tmp);
		ft_strdel(&(*tablo)[i_tmp]);
		(*tablo)[i_tmp] = ft_strdup(tmp2);
		ft_strdel(&tmp2);
	}
	if (!(*tablo)[1])
		ft_malloc_cmd(tablo, "");
	ft_malloc_cmd(tablo, "");
	*find_cursor = -1;
}

static void	beforeornext(char ***tablo, char *tmp, int i_tmp)
{
	char *tmp2;

	if (!*tablo)
		ft_malloc_cmd(tablo, tmp);
	else
	{
		i_tmp = ft_tablen(*tablo) - 1;
		tmp2 = ft_strjoin((*tablo)[i_tmp], tmp);
		ft_strdel(&(*tablo)[i_tmp]);
		(*tablo)[i_tmp] = ft_strdup(tmp2);
		ft_strdel(&tmp2);
	}
}

static char	**manage_tabsplit(const char *s, int i_tmp, int find_cursor,
		int cursor_pos)
{
	char	**tablo;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tablo = NULL;
	while (s[i])
	{
		i_tmp = lex_tab(s, i, &find_cursor, &cursor_pos);
		tmp = ft_strsub(s, i, i_tmp);
		i += i_tmp;
		if (find_cursor == 1)
			ft_find_word(&tablo, tmp, &find_cursor, i_tmp);
		else if (find_cursor == 2)
			ft_find_space(&tablo, tmp, &find_cursor, i_tmp);
		else
			beforeornext(&tablo, tmp, i_tmp);
		ft_strdel(&tmp);
	}
	!tablo ? ft_malloc_cmd(&tablo, "") : 0;
	!tablo[1] ? ft_malloc_cmd(&tablo, "") : 0;
	!tablo[2] ? ft_malloc_cmd(&tablo, "") : 0;
	return (tablo);
}

char		**ft_tabsplit(void)
{
	int		i_tmp;
	int		find_cursor;
	char	**ret;

	find_cursor = 0;
	ret = NULL;
	i_tmp = 0;
	if (g_cmd)
		ret = manage_tabsplit(g_cmd, i_tmp, find_cursor, g_cursor_pos);
	else
	{
		ft_malloc_cmd(&ret, "");
		ft_malloc_cmd(&ret, "");
		ft_malloc_cmd(&ret, "");
	}
	return (ret);
}
