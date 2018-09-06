/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 05:52:29 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/12 04:10:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char		**ft_tabdup(char **tab)
{
	char		**ret;
	int			i;

	i = -1;
	ret = NULL;
	if (!tab)
		return (NULL);
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1))))
		return (NULL);
	while (tab[++i])
		ret[i] = ft_strdup(tab[i]);
	ret[i] = NULL;
	return (ret);
}
