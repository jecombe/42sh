/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_size_term.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/25 11:00:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/29 15:35:48 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

void	ft_get_size_term(t_ws *ws, t_select **t, int fd)
{
	if (ioctl(fd, TIOCGWINSZ, &(*ws)) == -1)
		ft_error("ft_get_size_term", &(*t));
}
