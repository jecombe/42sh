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

int			init_shell(int ac, const char **av)
{
	char	*path;

	if (!(path = search_path_of_101sh(av[0])))
		return (EXIT_FAILURE);
	if (init_files(av[0]))
		return (EXIT_FAILURE);
	if (init_env(ac, av))
		return (EXIT_FAILURE);
	if (init_set(ac, av))
		return (EXIT_FAILURE);
	if (init_builtins((const char *)path))
		return (EXIT_FAILURE);
	ft_strdel(&path);
	return (EXIT_SUCCESS);
}
