/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 00:36:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 03:50:24 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*str_return;
	int		i;

	str_return = NULL;
	if (s)
	{
		i = ft_strlen(s);
		if (!(str_return = malloc(sizeof(char) * i + 1)))
			return (NULL);
		str_return[i] = '\0';
		i = -1;
		while (s[++i])
			str_return[i] = s[i];
	}
	return (str_return);
}
