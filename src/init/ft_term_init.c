/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 02:03:13 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_term_init(int ac, char **av)
{
	char			*term;

	if (init_files(av[0]))
		return (EXIT_FAILURE);
	if (init_env(ac, av))
		return (EXIT_FAILURE);
	if (init_set(ac, av))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
