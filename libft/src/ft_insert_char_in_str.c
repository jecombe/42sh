/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_insert_char_in_str.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/31 11:59:11 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 06:04:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_insert_char_in_str(char **str, char c, int at)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!(*str))
		return (1);
	if (!(ret = (char*)malloc(sizeof(char) * (ft_strlen(*str) + 2))))
		return (1);
	while ((*str)[i])
	{
		if (i == at && i == j)
			ret[j] = c;
		else
		{
			ret[j] = (*str)[i];
			i++;
		}
		j++;
	}
	ret[j] = '\0';
	ft_strdel(&(*str));
	return (0);
}
