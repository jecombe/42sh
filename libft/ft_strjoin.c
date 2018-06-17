/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lkasaria <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 19:14:11 by lkasaria     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/01 23:42:18 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ret;
	char	*p;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ret = (char*)malloc(len)))
		return (NULL);
	p = ret;
	s = (char*)s1;
	while (*(s++))
		*(p++) = *(s - 1);
	s = (char*)s2;
	while (*(s++))
		*(p++) = *(s - 1);
	*p = 0;
	return (ret);
}
