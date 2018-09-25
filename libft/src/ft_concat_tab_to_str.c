/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_concat_tab_to_str.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 01:29:16 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 01:37:26 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_concat_tab_to_str(char **tablo, char **str)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	while (tablo[++i])
		len += ft_strlen(tablo[i]);
	*str = (char*)malloc(sizeof(char) * (len + 1));
	i = -1;
	len = 0;
	while (tablo[++i])
	{
		j = 0;
		while (tablo[i][j])
			(*str)[len++] = tablo[i][j++];
	}
	(*str)[len] = '\0';
	return (0);
}
