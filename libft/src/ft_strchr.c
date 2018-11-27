/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:12:38 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 02:29:42 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		if (*s == (char)c)
			return ((char *)s);
		while (*s++)
			if (*s == (char)c)
				return ((char *)s);
	}
	return (NULL);
}
