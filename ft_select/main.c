/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 04:39:49 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/23 04:40:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include <stdio.h>
#include "includes/ft_select.h"

int                             main(int ac, char **av)
{
	int			line = 0;
	char		*str;
	(void)ac;
	str = ft_select(av, &line);
	printf("RETURN == %s\nLINE == %d\n", str, line);
	ft_strdel(&str);
	return (0);
}
