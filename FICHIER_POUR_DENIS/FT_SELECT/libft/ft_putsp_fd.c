/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putsp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/18 16:18:36 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/13 05:26:06 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putsp_fd(int fd, int before_sp, char *str, int nb_sp)
{
	int		i;

	i = -1;
	while (++i < before_sp)
		ft_putstr_fd(" ", fd);
	if (str)
		ft_putstr_fd(str, fd);
	i = -1;
	while (++i < nb_sp)
		ft_putstr_fd(" ", fd);
}
