/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/03 00:50:51 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/22 21:52:33 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"
/*
int		ft_count_line(t_select *t)
{
	int		params;
	int		line;;

	params = ft_count_params(t->line);
	line = ft_params_by_line(t);
//	printf("PARAMS == %d\n", params);
//	printf("LINE == %d\n", line);
//	sleep(2);
	if (line > 0 && (params % line) == 0)
		return (params / line);
	else
		return (params / (line + 1));*/
/*		return (ft_count_params(t->line) % ft_params_by_line(t) == 0 ?
		ft_count_params(t->line) / ft_params_by_line(t) :
		ft_count_params(t->line) / ft_params_by_line(t) + 1);*/
//}

int		ft_count_line(t_select *t)
{
	return (ft_count_params(t->line) % ft_params_by_line(t) == 0 ?
	ft_count_params(t->line) / ft_params_by_line(t) :
	ft_count_params(t->line) / ft_params_by_line(t) + 1);
}
