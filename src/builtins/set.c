/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 06:50:50 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 06:55:27 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

/*
 * LES REDIRECTIONS NE SONT PAS FAITES
*/

int		set(t_op *exec)
{
	int		i;

	i = 0;
	if (!exec->cmd[1])
		while (g_set[i])
			ft_putendl(g_set[i++]);
	return (0);
}
