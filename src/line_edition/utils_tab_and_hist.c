/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_tab_and_hist.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/30 12:37:19 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 16:13:14 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	key_for_tab(char key[5])
{
	if ((key[0] == 9 && key[1] == 0 && key[2] == 0 && key[3] == 0) ||
		(key[0] == 10 && key[1] == 0 && key[2] == 0 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == 65 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == 66 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == 67 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == 68 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == -101 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == -102 && key[3] == 0))
		return (1);
	return (0);
}

static int	key_for_hist(char key[5])
{
	if ((key[0] == 27 && key[1] == 91 && key[2] == 65 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == 66 && key[3] == 0) ||
		(key[0] == 27 && key[1] == 91 && key[2] == -101 && key[3] == 0))
		return (1);
	return (0);
}

void		init_tab_and_hist(t_shell *sh, char key[5])
{
	if (sh->tmp_line && sh->hist == -1 && sh->tabu == -2)
		ft_strdel(&sh->tmp_line);
	init_tab(sh, key);
	init_hist(sh, key);
}

void		init_tab(t_shell *sh, char key[5])
{
	if (sh->tabu != -1 && !key_for_tab(key))
	{
		tabulator(&sh, 0, NULL);
		ft_strdel(&sh->tmp_line);
		sh->tabu = -1;
	}
}

void		init_hist(t_shell *sh, char key[5])
{
	if (sh->hist != -2 && !key_for_hist(key))
	{
		sh->hist = -2;
		ft_strdel(&sh->tmp_line);
	}
}
