/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_read_entry.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:22:52 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 14:19:21 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

char	*ft_read_entry(t_select **t)
{
	char	c[6];
	int		ret;

	ft_memset(&c, 0, sizeof(char) * 6);
	ret = 0;
	if ((ret = read(STDIN_FILENO, c, 5)) == -1)
	{
		ft_memset(&c, 0, sizeof(char) * 6);
		ft_error("read", &(*t));
	}
	else
		c[ret] = '\0';
	/*c[0] = -1;
	c[1] = 0;
	c[2] = 0;
	c[3] = 0;
	c[4] = 0;
	c[5] = 0;
	ret = read(STDIN_FILENO, c, 5);
	if (ret == -1)
		ft_error("read", &(*t));
	if ((int)c[0] != -1)
	{
		c[ret] = '\0';
	}
	if ((int)c[0] == -1)
	{
		c[1] = 0;
		c[2] = 0;
		c[3] = 0;
		c[4] = 0;
		c[5] = 0;
	}*/
	return (ft_strdup(c));
}
