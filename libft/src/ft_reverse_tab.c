/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_reverse_tab.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 07:39:43 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/16 08:10:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

int		ft_reverse_tab(char ***tablo)
{
	int		i;
	int		j;
	char	**tmp;

	if (*tablo)
	{
		i = ft_tablen(*tablo) - 1;
		j = 0;
		if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
			return (1);
		while (i >= 0)
			tmp[j++] = ft_strdup((*tablo)[i--]);
		tmp[j] = NULL;
		ft_tabdel(tablo);
		*tablo = ft_tabdup(tmp);
		ft_tabdel(&tmp);
	}
	return (0);
}
