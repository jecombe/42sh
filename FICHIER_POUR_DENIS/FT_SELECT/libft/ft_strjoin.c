/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 00:37:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 00:37:29 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str_return;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(s1 && s2))
		return (0);
	len = (ft_strlen(s1)) + (ft_strlen(s2));
	if (!(str_return = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	while (s1[i] || s2[j])
	{
		str_return[i + j] = s1[i] ? ((char*)s1)[i] : ((char*)s2)[j];
		s1[i] ? i++ : j++;
	}
	str_return[i + j] = '\0';
	return (str_return);
}
