/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:37:46 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 02:33:03 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(char const *src)
{
	char *dest;

	if (!(dest = (char*)malloc(sizeof(char) * ft_strlen(src) + 1)))
		return (NULL);
	dest = ft_strcpy(dest, src);
	return (dest);
}
