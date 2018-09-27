/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_addstrtostrat.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/27 10:25:18 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:56:26 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_addstrtostrat(char **str, char *to_add, int at)
{
	int		i;
	char	*tmp;
	int		j;
	int		add;

	add = 0;
	j = 0;
	i = 0;
	if (*str && to_add && at < (int)ft_strlen(*str) && at >= 0)
	{
		i = ft_strlen(*str) + ft_strlen(to_add);
		if (!(tmp = (char*)malloc(sizeof(char) * (i + 1))))
			return (1);
		i = 0;
		while ((*str)[i])
		{
			if (i == at)
				while(to_add[j])
					tmp[add++] = to_add[j++];
			tmp[add++] = (*str)[i++];
		}
		tmp[add] = '\0';
		ft_strdel(str);
		*str = ft_strdup(tmp);
	}
	return (0);
}
