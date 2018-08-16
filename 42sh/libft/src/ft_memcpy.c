/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:11:15 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:02 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	int		i;

	dest = (char *)dst;
	i = -1;
	while (++i < (int)n)
		dest[i] = ((char *)src)[i];
	return (dest);
}
