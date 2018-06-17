/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:37:46 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/26 00:00:06 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *src)
{
	char *dest;

	if (!(dest = (char*)malloc(sizeof(char) * ft_strlen(src) + 1)))
		return (NULL);
	dest = ft_strcpy(dest, src);
	return (dest);
}
