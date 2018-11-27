/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add_str_at.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 03:40:49 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 07:28:44 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

static int		annexe(char ***tablo, char *str, int at, char ***tmp)
{
	int			i;

	i = 0;
	while ((*tablo)[i])
	{
		if (i == at)
		{
			if (ft_malloc_cmd(tmp, str))
				return (1);
			at = -1;
		}
		else
		{
			if (ft_malloc_cmd(tmp, (*tablo)[i++]))
				return (1);
		}
	}
	ft_tabdel(tablo);
	return (0);
}

int				ft_add_str_at(char ***tablo, char *str, int at)
{
	char		**tmp;

	tmp = NULL;
	if (*tablo)
	{
		if (annexe(tablo, str, at, &tmp))
			return (1);
	}
	else
		ft_malloc_cmd(&tmp, str);
	if (!(*tablo = ft_tabdup(tmp)))
		return (1);
	ft_tabdel(&tmp);
	return (0);
}
