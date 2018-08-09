/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ocurences.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/13 19:29:58 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/13 19:32:36 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_ocurences(const char *str, char c)
{
	int i;
	int counter;

	if (!str)
		return (0);
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}
