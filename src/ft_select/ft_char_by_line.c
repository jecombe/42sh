/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_char_by_line.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 06:14:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 14:25:21 by gmadec      ###    #+. /#+    ###.fr     */
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
