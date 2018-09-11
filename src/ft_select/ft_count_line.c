/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/03 00:50:51 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:09:52 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_count_line(t_select *t)
{
	return (ft_count_params(t->line) % ft_params_by_line(t) == 0 ?
	ft_count_params(t->line) / ft_params_by_line(t) :
	ft_count_params(t->line) / ft_params_by_line(t) + 1);
}
