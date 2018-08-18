/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:14:16 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:36 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	if (*s == (char)c)
		return ((char *)s);
	while (i > 0)
	{
		i--;
		s--;
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}
