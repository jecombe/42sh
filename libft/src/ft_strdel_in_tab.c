/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdel_in_tab.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 06:17:47 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 05:52:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strdel_in_tab(char ***tablo, int index)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if ((*tablo)[1])
	{
		while (i < index)
			if (ft_malloc_cmd(&tmp, (*tablo)[i++]))
				return (1);
		i++;
		while ((*tablo)[i])
			if (ft_malloc_cmd(&tmp, (*tablo)[i++]))
				return (1);
		ft_tabdel(&(*tablo));
		if (!(*tablo = ft_tabdup(tmp)))
			return (1);
	}
	else
		ft_tabdel(&(*tablo));
	return (0);
}
