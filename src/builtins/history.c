/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 02:27:55 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 12:01:53 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		advanced_history(char ***history, char *base)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = NULL;
	while ((*history)[++i])
		if (!ft_strncmp(base, (*history)[i], ft_strlen(base)))
			ft_malloc_cmd(&tmp, (*history)[i]);
	ft_tabdel(history);
	if (tmp)
		*history = ft_tabdup(tmp);
	ft_tabdel(&tmp);
	return (0);
}

static void		cut_crochet_historic(char ***history)
{
	char	**tmp;
	char	*tmp_2;
	int		i;

	i = -1;
	tmp = NULL;
	if (*history)
	{
		while (*history && (*history)[++i])
			if ((*history)[i][0] == '[' &&
				(*history)[i][ft_strlen((*history)[i]) - 1] == ']')
			{
				tmp_2 = ft_strsub((*history)[i], 1,
						ft_strlen((*history)[i]) - 2);
				ft_malloc_cmd(&tmp, tmp_2);
				free(tmp_2);
			}
		ft_tabdel(history);
		if (tmp)
			*history = ft_tabdup(tmp);
		ft_tabdel(&tmp);
	}
}

static void		the_last_of_dowm(t_shell *sh)
{
	sh->hist = -2;
	ft_pushed_key_home_end(sh, FT_KEY_HOME);
	TERMCAP("cd");
	ft_strdel(&g_cmd);
	if (sh->tmp_line)
	{
		g_cmd = ft_strdup(sh->tmp_line);
		ft_strdel(&sh->tmp_line);
		ft_putstr(g_cmd);
	}
	g_cursor_pos = g_cmd ? ft_strlen(g_cmd) : 0;
}

static void		heart_of_hist_search(t_shell *sh, char **history, char key[])
{
	if (sh->hist == -2)
		sh->hist = -1;
	if (key[2] == 65)
		sh->hist++;
	else
		sh->hist--;
	ft_pushed_key_home_end(sh, FT_KEY_HOME);
	TERMCAP("cd");
	if (sh->hist >= 0)
	{
		ft_strdel(&g_cmd);
		g_cmd = ft_strdup(history[sh->hist]);
		ft_putcmd(sh, ft_strlen(g_cmd));
	}
}

void			history_get(t_shell *sh, char key[])
{
	char		**history;

	history = NULL;
	history_save(&history, NULL, 0, (char *)NULL);
	ft_reverse_tab(&history);
	cut_crochet_historic(&history);
	if (history && key[2] == 65 && sh->hist == -2 && g_cmd)
		sh->tmp_line = ft_strdup(g_cmd);
	if (history && sh->tmp_line)
		advanced_history(&history, sh->tmp_line);
	if (history)
	{
		if ((sh->hist + 1 < ft_tablen(history) && key[2] == 65) ||
			(sh->hist >= 0 && key[2] == 66) || (sh->hist == -2 && key[2] == 65))
			heart_of_hist_search(sh, history, key);
		if (key[2] == 66 && sh->hist == -1 && g_cmd)
			the_last_of_dowm(sh);
		ft_tabdel(&history);
	}
	else
		ft_strdel(&sh->tmp_line);
}
