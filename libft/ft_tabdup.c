/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/27 23:51:01 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/28 00:09:21 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	int i;
	char **tabnew;

	i = -1;
	if (!(tabnew = (char**)malloc(sizeof(char*) * ft_tablen(tab) + 1)))
		return (NULL);
	while (tab[++i])
		tabnew[i] = ft_strdup(tab[i]);
	tabnew[i] = NULL;
	return (tabnew);
}
