/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:14:26 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:39 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s)
	{
		i = -1;
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (++i < (int)len)
		{
			str[i] = s[start];
			start++;
		}
		return (str);
	}
	return (NULL);
}
