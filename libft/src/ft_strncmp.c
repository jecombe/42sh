/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncmp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:13:51 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 14:46:47 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t len)
{
	int		i;

	i = -1;
	while (++i != (int)len)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if ((!s1[i]) || (!s2[i]))
			return (0);
	}
	return (0);
}
