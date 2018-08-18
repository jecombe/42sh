/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:13:27 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:27 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dst_size;
	size_t src_size;

	i = 0;
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (size > 1)
	{
		while (src[i] != '\0' && ((dst_size + i) < (size - 1)))
		{
			dst[dst_size + i] = src[i];
			i++;
		}
	}
	dst[dst_size + i] = '\0';
	return (src_size + ((dst_size < size) ? dst_size : size));
}
