/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 05:52:29 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:41:26 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char		**ft_tabdup(char **tab)
{
	int		i;
	char	**ret;

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
