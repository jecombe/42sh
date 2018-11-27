/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_mini_printf.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 14:23:11 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 07:40:10 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

/*
**    ft_geoprintf():
**        Un mini printf/sprintf (pour les %d et %s) avec systeme de buffer
**        A utiliser avec un buffer de taille fixe avec des \0 au preallable
**        Si le buffer est NULL, print directe sur la sortie standart
*/

void			ft_geoprintf(char *buff, const char *s, ...)
{
	va_list		args;
	char		*tmp;
	char		buff_2[4096];
	char		*my_buff;

	if (!(my_buff = buff))
	{
		ft_bzero(buff_2, sizeof(buff_2));
		my_buff = buff_2;
	}
	va_start(args, s);
	while (*s)
		if (!ft_strncmp(s, "%d", 2) && (s += 2))
		{
			tmp = ft_itoa(va_arg(args, int));
			ft_strcat(my_buff, tmp);
			free(tmp);
		}
		else if (!ft_strncmp(s, "%s", 2) && (s += 2))
			ft_strcat(my_buff, va_arg(args, char*));
		else
			ft_strncat(my_buff, s++, 1);
	if (!buff)
		write(1, buff_2, ft_strlen(buff_2));
	va_end(args);
}
