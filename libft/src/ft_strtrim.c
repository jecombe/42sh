/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:14:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:40 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strtrim(const char *s)
{
	size_t	i;
	size_t	min;
	size_t	max;
	char	*str;

	i = 0;
	if (s)
	{
		while ((ft_isblank(s[i]) || s[i] == '\n') && s[i + 1])
			i++;
		min = i;
		while (s[i + 1])
			i++;
		while ((ft_isblank(s[i]) || s[i] == '\n') && i > min)
			i--;
		max = min == i ? i : i + 1;
		if (!(str = ft_strsub(s, min, ((max - min)))))
			return (NULL);
		return (str);
	}
	return (NULL);
}
