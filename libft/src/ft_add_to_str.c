/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add_to_str.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/15 00:16:54 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 00:26:12 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_add_to_str(char **str, char c)
{
	char		*tmp;
	int			i;

	i = 0;
	if (*str)
	{
		if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(*str) + 2))))
		{
			ft_strdel(str);
			return (1);
		}
		while ((*str)[i])
		{
			tmp[i] = (*str)[i];
			i++;
		}
	}
	else
		if (!(tmp = (char*)malloc(sizeof(char) * 2)))
		{
			ft_strdel(str);
			return (1);
		}
	tmp[i] = c;
	tmp[i] = '\0';
	return (0);
}
