/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:14:11 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 20:16:22 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		f;

	i = 0;
	f = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + f] == needle[f] && i + f < len)
		{
			f++;
			if (needle[f] == '\0')
			{
				while (i--)
					haystack++;
				return ((char *)haystack);
			}
		}
		f = 0;
		i++;
	}
	return (NULL);
}
