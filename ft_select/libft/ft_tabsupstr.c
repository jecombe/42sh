/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabsupstr.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/03 20:36:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/23 09:57:26 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_tabsupstr(char **tab, int ac, char *(dup)(const char *s))
{
	int			i;
	int			j;
	char		**tmp;
	int			len;
	static	int	pass = 0;

	len = ft_tablen(tab - 1);
	if (ac >= len || ac == 0)
		return (tab);
	i = -1;
	j = 0;
	if (!(tmp = (char**)malloc(sizeof(char*) * len - 1)))
		return (0);
	while (tab[++i])
		if (!(i + 1 == ac))
		{
			tmp[j] = dup(tab[i]);
			j++;
		}
	if (pass > 0)
		free(tab);
	tmp[j] = NULL;
	pass++;
	return (tmp);
}
