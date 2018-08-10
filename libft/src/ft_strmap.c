/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:13:37 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:29 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	size_t	i;

	i = -1;
	if (s)
	{
		if (!(str = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (s[++i])
			str[i] = f(str[i]);
		return (str);
	}
	return (NULL);
}
