/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:35:54 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/22 21:35:55 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *tmp_dst;
	unsigned char *tmp_src;

	tmp_dst = (unsigned char*)dst;
	tmp_src = (unsigned char*)src;
	if (dst <= src && src <= dst + len - 1)
		while (len--)
			*tmp_dst++ = *tmp_src++;
	else
	{
		tmp_dst += len - 1;
		tmp_src += len - 1;
		while (len--)
			*tmp_dst-- = *tmp_src--;
	}
	return (dst);
}
