/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_count.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 09:23:51 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 10:29:42 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

int		ft_char_by_line(t_select **sel)
{
	int		res;
	int		nb_arg;

	nb_arg = ft_count_params((*sel)->line);
	if (nb_arg == 1)
		res = ft_search_big_param((*sel)->line);
	else
		res = ft_search_big_param((*sel)->line) * nb_arg + 1 * nb_arg - 1;
	return (res);
}

int		ft_count_line(t_select *t)
{
	if (ft_params_by_line(t))
	{
		return (ft_count_params(t->line) % ft_params_by_line(t) == 0 ?
				ft_count_params(t->line) / ft_params_by_line(t) :
				ft_count_params(t->line) / ft_params_by_line(t) + 1);
	}
	return (0);
}

int		ft_count_params(t_line *line)
{
	int		i;

	i = 0;
	while (line)
	{
		line = line->next;
		i++;
	}
	return (i);
}
