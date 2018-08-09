/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/27 21:47:57 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/29 12:32:41 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*mal;

	i = 0;
	mal = NULL;
	if (s != 0)
	{
		mal = ft_memalloc(len + 1);
		if (mal == 0)
			return (NULL);
		while (i != len)
		{
			mal[i] = s[start];
			i++;
			start++;
		}
		mal[i] = '\0';
		return (mal);
	}
	return (NULL);
}
