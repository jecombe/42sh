/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/27 21:46:54 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 19:22:35 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
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
			mal[i] = f(s[i]);
			i++;
		}
		mal[i] = '\0';
		return (mal);
	}
	return (NULL);
}
