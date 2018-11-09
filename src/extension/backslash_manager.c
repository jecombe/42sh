/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backslash_manager.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 20:13:12 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 04:37:12 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

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
	ft_strdel(&tmp);
	return (0);
}

int			backslash_manager(char ***cmd, t_bquote **i)
{
	if (*cmd && (*cmd)[(*i)->i][(*i)->j] == '\\')
	{
		if ((*i)->dquote == 0)
		{
			if (backslash_out_dquote(&(*cmd)[(*i)->i], &(*i)->j))
				return (-1);
		}
		else
			(*i)->j = (*i)->j + 1;
		return (1);
	}
	return (0);
}
