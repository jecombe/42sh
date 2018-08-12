/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wordlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:14:55 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 20:16:29 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t		ft_wordlen(const char *s, char c, size_t i)
{
	size_t	count;

	count = 0;
	if (s)
	{
		while (s[i] != c && s[i] != '\0')
		{
			count++;
			i++;
		}
	}
	return (count);
}
