/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/03 12:54:02 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/14 18:32:42 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		ft_tabrev(char ***tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_tablen((*tab) - 1);
	tmp = NULL;
	if (*tab)
	{
		while (i < j)
		{
			tmp = ft_strdup((*tab)[i]);
			(*tab)[i] = ft_strdup((*tab)[j]);
			(*tab)[j] = ft_strdup(tmp);
			i++;
			j--;
		}
	}
	ft_strdel(&tmp);
}
