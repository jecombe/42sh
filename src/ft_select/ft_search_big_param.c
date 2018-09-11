/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_search_big_param.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 01:26:02 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:10:07 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_search_big_param(t_line *line)
{
	t_line		*tmp;
	size_t		len_max;

	len_max = 0;
	tmp = line;
	while (tmp)
	{
		if (ft_strlen(tmp->elem) > len_max)
			len_max = ft_strlen(tmp->elem);
		tmp = tmp->next;
	}
	return (len_max);
}
