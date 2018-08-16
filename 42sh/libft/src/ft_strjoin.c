/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:13:22 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:26 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	char	*str;

	i = 0;
	if (s1 && s2)
	{
		if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
			return (NULL);
		while (*s1)
		{
			str[i] = *s1;
			s1++;
			i++;
		}
		while (*s2)
		{
			str[i] = *s2;
			s2++;
			i++;
		}
		return (str);
	}
	return (NULL);
}
