/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strequ.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:37:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/22 21:37:53 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if ((s1 == NULL || s2 == NULL))
		return (i = s1 == NULL && s2 == NULL ? 1 : 0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (i = s1[i] == s2[i] ? 1 : 0);
}
