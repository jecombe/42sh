/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_malloc_cmd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 05:53:21 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 03:53:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

int			ft_malloc_cmd(char ***cmd, char *new_arg)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(*cmd) && new_arg)
	{
		if (!(tab = (char**)malloc(sizeof(char*) * 2)))
			return (1);
	}
	else if (new_arg)
	{
		if (!(tab = (char**)malloc(sizeof(char*) * (ft_tablen(*cmd) + 2))))
			return (1);
		i = -1;
		while ((*cmd)[++i])
			tab[i] = ft_strdup((*cmd)[i]);
	}
	else
		return (0);
	tab[i] = ft_strdup(new_arg);
	tab[i + 1] = NULL;
	*cmd = ft_tabdup(tab);
	return (0);
}
