/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:11:30 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 20:15:44 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*srce;
	char		*dest;

	srce = src;
	dest = dst;
	if (srce <= dest)
	{
		srce += len - 1;
		dest += len - 1;
		while (len--)
			*dest-- = *srce--;
	}
	else
		ft_memcpy(dest, srce, len);
	return (dst);
}
