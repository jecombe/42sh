/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_params_by_line.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:27:16 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/27 13:27:17 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

int		ft_params_by_line(t_select *t)
{
	int		ret;
	int		i;
	int		big_param;
	int		nb_char;

	ret = 0;
	i = 0;
	nb_char = 0;
	big_param = ft_search_big_param(t->line);
	while (i != -1 && t->line)
	{
		if (nb_char == 0 && nb_char + big_param <= t->ws.ws_col)
			ret++;
		else if (nb_char + big_param + 1 <= t->ws.ws_col)
			ret++;
		else
			i = -1;
		nb_char += ret == 0 ? big_param : big_param + 1;
	}
	return (ret);
}
