/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_malloc_cmd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 05:53:21 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 14:43:35 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int			ft_malloc_cmd(char ***cmd, char *new_arg)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	if (!new_arg)
		return (EXIT_SUCCESS);
	if (*cmd)
		if ((tab = ft_tabdup(*cmd)))
			ft_tabdel(&(*cmd));
	if (!(*cmd = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 2))))
		return (EXIT_FAILURE);
	if (tab)
		while (tab[i])
		{
			(*cmd)[i] = ft_strdup(tab[i]);
			i++;
		}
	(*cmd)[i] = ft_strdup(new_arg);
	(*cmd)[i + 1] = NULL;
	ft_tabdel(&tab);
	return (EXIT_SUCCESS);
}
