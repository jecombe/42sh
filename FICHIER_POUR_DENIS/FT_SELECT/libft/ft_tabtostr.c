/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabtostr.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 12:59:41 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/27 12:59:44 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_cmptr_char(char **tab, int i, int j)
{
	int		cmp;

	cmp = 0;
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			cmp++;
	}
	return (cmp += i);
}

char	*ft_tabtostr(char **tab)
{
	char	*str;
	int		i;
	int		j;
	int		i_str;

	str = NULL;
	i = -1;
	i_str = 0;
	j = 0;
	if (tab)
	{
		str = malloc(sizeof(char*) * ft_cmptr_char(tab, i, j) + 1);
		while (tab[++i])
		{
			j = -1;
			while (tab[i][++j])
				str[i_str++] = tab[i][j];
		}
		str[i_str] = '\0';
	}
	return (str);
}
