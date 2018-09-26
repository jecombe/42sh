/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:13:55 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:32 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;

	i = -1;
	while (src[++i] && i < (int)len)
		dst[i] = src[i];
	while (i < (int)len)
		dst[i++] = '\0';
	return (dst);
}
