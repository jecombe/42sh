/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_stradel.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 14:25:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:16 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_stradel(char ***array)
{
	int i;

	i = -1;
	while ((*array)[++i])
		ft_strdel(&(*array)[i]);
	ft_strdel(&(*array)[i]);
	free(*array);
}
