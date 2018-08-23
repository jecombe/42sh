/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 00:36:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 04:35:21 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str_return;
	int		i;

	i = ft_strlen(s);
	if (!(str_return = malloc(sizeof(char) * i + 1)))
		return (0);
	str_return[i] = '\0';
	i = -1;
	while (s[++i])
		str_return[i] = s[i];
	return (str_return);
}
