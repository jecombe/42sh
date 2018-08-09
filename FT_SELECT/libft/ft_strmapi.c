/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/27 21:47:00 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/29 12:32:05 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*mal;
	size_t	i;

	i = 0;
	if (s != 0)
	{
		while (s[i])
			i++;
		mal = ft_memalloc(i + 1);
		if (mal == 0)
			return (NULL);
		i = 0;
		while (s[i])
		{
			mal[i] = f(i, s[i]);
			i++;
		}
		mal[i] = '\0';
		return (mal);
	}
	return (NULL);
}
