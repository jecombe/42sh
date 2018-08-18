/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wordcount.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:14:51 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:42 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

size_t		ft_wordcount(const char *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			while (s[i] == c && s[i])
				i++;
			while (s[i] != c && s[i])
			{
				if (s[i + 1] == c || !(s[i + 1]))
					count++;
				i++;
			}
		}
	}
	return (count);
}
