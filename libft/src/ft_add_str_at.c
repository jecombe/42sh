/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add_str_at.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 03:40:49 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 10:50:21 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int			ft_add_str_at(char ***tablo, char *str, int at)
{
	char		**tmp;
	int			i;

	i = 0;
	tmp = NULL;
	while ((*tablo)[i])
	{
		if (i == at)
		{
			if (ft_malloc_cmd(&tmp, str))
				return (1);
			at = -1;
		}
		else
			if (ft_malloc_cmd(&tmp, (*tablo)[i++]))
				return (1);
	}
	*tablo ? ft_tabdel(tablo) : 0;
	if (tmp)
	{
		if (!(*tablo = ft_tabdup(tmp)))
			return (1);
		ft_tabdel(&tmp);
	}
	return (0);
}
