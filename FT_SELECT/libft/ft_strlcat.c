/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/29 18:08:38 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/29 18:13:36 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dest, const char *restrict src, size_t l)
{
	size_t i;
	size_t j;

	i = ft_strlen(dest);
	j = ft_strlen(src);
	if (l <= i)
		return (l + j);
	ft_strncat(dest, src, l - i - 1);
	return (i + j);
}
