/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:13:47 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:30 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = ft_strlen(s1);
	while (++i < n && s2[i])
		s1[len + i] = s2[i];
	s1[len + i] = '\0';
	return (s1);
}
