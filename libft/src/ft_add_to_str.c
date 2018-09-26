/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add_to_str.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/15 00:16:54 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 12:40:44 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"



int		ft_add_to_str(char **str, char c, int index)
{
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (*str)
	{
		if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(*str) + 2))))
			return (1);
		while ((*str)[i] && i < index)
			tmp[j++] = (*str)[i++];
		tmp[j++] = c;
		while ((*str)[i])
			tmp[j++] = (*str)[i++];
	}
	else
	{
		if (!(tmp = (char*)malloc(sizeof(char) * 2)))
			return (1);
		tmp[j++] = c;
	}
	tmp[j] = '\0';
	ft_strdel(str);
	*str = ft_strdup(tmp);
	return (0);
}
