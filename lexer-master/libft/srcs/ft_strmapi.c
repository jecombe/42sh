/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:13:42 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/12 20:16:16 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = -1;
	if (s)
	{
		if (!(str = ft_strnew(ft_strlen(s))))
			return (NULL);
		str = ft_strcpy(str, s);
		while (s[++i])
			str[i] = f(i, str[i]);
		return (str);
	}
	return (NULL);
}
