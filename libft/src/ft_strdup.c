/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 00:36:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/07 01:01:10 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dest;

	i = -1;
	dest = NULL;
	if (!s1)
		return (NULL);
	if (!(dest = ft_strnew(ft_strlen(s1))))
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	return (dest);
}
