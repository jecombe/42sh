/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_read_entry.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:22:52 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 01:27:54 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"
#include <stdio.h>

char	*ft_read_entry(t_select **t)
{
	char	c[6];
	int		ret;

	c[0] = -1;
	c[1] = 0;
	c[2] = 0;
	c[3] = 0;
	c[4] = 0;
	c[5] = 0;
	ret = read(STDIN_FILENO, c, 5);
	if (ret == -1)
		ft_error("read", &(*t));
	if (c[0] != -1)
	{
		c[ret] = '\0';
	}
	if (c[0] == -1)
	{
		c[1] = 0;
		c[2] = 0;
		c[3] = 0;
		c[4] = 0;
		c[5] = 0;
	}
	return (ft_strdup(c));
}
