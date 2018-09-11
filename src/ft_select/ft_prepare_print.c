/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_prepare_print.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 18:14:17 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:10:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

t_line		*ft_prepare_print(int i[2], t_line **line, int nb_line)
{
	int		at_print;
	t_line	*tmp;
	int		bp;

	bp = ft_search_big_param(*line);
	tmp = *line;
	at_print = i[0] + (nb_line * i[1]);
	while (at_print && tmp->next)
	{
		tmp = tmp->next;
		at_print--;
	}
	tmp->x_char_pos = i[1] * bp + i[1];
	tmp->x_param_pos = i[1];
	tmp->y_pos = i[0];
	return (tmp);
}
