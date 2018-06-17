/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:40:03 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/22 21:40:04 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = ft_strlen(needle);
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && j < k)
			j++;
		if (haystack[i + j - 1] == needle[j - 1] && j == k)
			return ((char*)haystack + i);
		j = 0;
		i++;
	}
	return (needle[0] == '\0' ? (char*)haystack : 0);
}
