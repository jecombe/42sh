/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backslash_manager.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 20:13:12 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 15:37:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	escpape_charspec(char c)
{
	if (c == '$' || c == '`' || c == '"' || c == '\\')
		return (1);
	return (0);
}

int			backslash_manager(char ***cmd, t_bquote **i)
{
	if (*cmd && (*cmd)[(*i)->i][(*i)->j] == '\\')
	{
		if ((*i)->dquote == 0 && (*cmd)[(*i)->i][(*i)->j + 1] != '\n')
			ft_chardel_at(&(*cmd)[(*i)->i], (*i)->j);
		else if ((*cmd)[(*i)->i][(*i)->j + 1] == '\n')
		{
			ft_chardel_at(&(*cmd)[(*i)->i], (*i)->j);
			ft_chardel_at(&(*cmd)[(*i)->i], (*i)->j);
			(*i)->j = (*i)->j - 1;
		}
		else
		{
			if (escpape_charspec((*cmd)[(*i)->i][(*i)->j + 1]))
				ft_chardel_at(&(*cmd)[(*i)->i], (*i)->j);
			else
				(*i)->j = (*i)->j + 1;
		}
		(*i)->j = (*i)->j + 1;
		return (1);
	}
	return (0);
}
