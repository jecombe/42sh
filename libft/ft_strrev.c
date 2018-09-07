/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 23:38:30 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 23:49:05 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp[ft_strlen(str) + 1];

	i = 0;
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		tmp[i] = str[len];
		i++;
		len--;
	}
	tmp[i] = '\0';
	ft_strcpy(str, tmp);
	return (str);
}
