/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add_str_at.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 03:40:49 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 03:50:13 by gmadec      ###    #+. /#+    ###.fr     */
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
			ft_malloc_cmd(&tmp, str);
			at = -1;
		}
		else
		{
			ft_malloc_cmd(&tmp, (*tablo)[i]);
			i++;
		}
	}
	*tablo ? ft_tabdel(tablo) : 0;
	if (tmp)
	{
		*tablo = ft_tabdup(tmp);
		ft_tabdel(&tmp);
	}
	return (0);
}
