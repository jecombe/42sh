/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_tab.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 11:04:32 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 11:19:46 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		binorfile(t_shell **ed, int *end_word)
{
	int			i;
	t_tab_lex	t;
	int			cursor;

	i = 0;
	(*ed)->t.nb_word = 0;
	while ((*ed)->t.cmd[0][i])
	{
		cursor = -1;
		t.c = (*ed)->t.cmd[0][i];
		t.i = i;
		t.count = 0;
		if (ft_is_echap_sep((*ed)->t.cmd[0], i))
			(*ed)->t.nb_word = 0;
		else if (ft_isprint((*ed)->t.cmd[0][i]))
			(*ed)->t.nb_word++;
		i++;
	}
	(*ed)->t.nb_char = 1;
	*end_word = ft_strlen((*ed)->t.cmd[0]) + ft_strlen((*ed)->t.cmd[1]);
}

int				lexer_tab(t_shell **sh)
{
	int		end_word;

	if (((*sh)->t.cmd = ft_tabsplit()))
	{
		binorfile(sh, &end_word);
		if (g_cursor_pos < end_word)
		{
			g_cursor_pos = end_word;
			return (-1);
		}
		else if ((*sh)->t.cmd[1][0])
			(*sh)->t.word = ft_strdup((*sh)->t.cmd[1]);
		if ((*sh)->t.word && (*sh)->t.word[0] == '$')
			(*sh)->t.nb_word = -1;
	}
	return (1);
}

int				echap_char(char **element)
{
	int			i;

	i = -1;
	while ((*element)[++i])
		if (ft_isechap((*element)[i]))
			ft_add_to_str(&*element, '\\', i++);
	return (0);
}

void			end_tab_sequence(t_shell *sh)
{
	TERMCAP("cd");
	ft_free_t_tab(&sh->t);
	ft_free_t_select(&sh->sel);
	sh->tabu = -1;
}
