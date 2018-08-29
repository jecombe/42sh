/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backslash_manager.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 20:13:12 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 05:26:59 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

int			backslash_out_dquote(char **cmd, int *j)
{
	char		*tmp;
	int			i;
	int			i2;

	i = 0;
	if (!(tmp = malloc(sizeof(char) * ft_strlen(*cmd))))
		return (1);
	while (i < *j)
	{
		tmp[i] = (*cmd)[i];
		i++;
	}
	i2 = i;
	i++;
	while ((*cmd)[i])
	{
		tmp[i2] = (*cmd)[i];
		i++;
		i2++;
	}
	tmp[i2] = '\0';
	ft_strdel(&(*cmd));
	*cmd = ft_strdup(tmp);
	tmp ? ft_strdel(&tmp) : 0;
	return (0);
}

int			backslash_manager(char ***cmd, t_bquote **i, int d_quote)
{
	if ((*cmd)[(*i)->i][(*i)->j] == '\\')
	{
		if (d_quote == 0)
		{
			if (backslash_out_dquote(&(*cmd)[(*i)->i], &(*i)->j))
				return (-1);
		}
		else
			(*i)->j = (*i)->j + 1;
		(*i)->j = (*i)->j + 1;
		return (1);
	}
	return (0);
}
