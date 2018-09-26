/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strreplace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/26 14:56:11 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/26 15:01:22 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strreplace(char ***tablo, int index, char *by)
{
	if (*tablo && (*tablo)[index])
	{
		ft_strdel(&(*tablo)[index]);
		(*tablo)[index] = ft_strdup(by);
	}
	return (0);
}
