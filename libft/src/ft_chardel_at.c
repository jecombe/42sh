/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_chardel_at.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/21 05:37:47 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 07:08:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_chardel_at(char **str, int at)
{
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (*str && (*str)[1])
	{
		if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(*str))))
			return (1);
		while ((*str)[i])
		{
			if (i != at)
				tmp[j++] = (*str)[i];
			i++;
		}
		tmp[j] = '\0';
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else if (*str)
		ft_strdel(str);
	return (0);
}
