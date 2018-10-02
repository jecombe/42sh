/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_position.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 04:13:30 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 17:45:12 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		get_row(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			break ;
		i++;
	}
	return (ft_atoi(str + i));
}

static int		get_col(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (i && str[i - 1] == ';' && str[i] >= '0' && str[i] <= '9')
			break ;
	return (ft_atoi(str + i));
}

static	int		cursor_position(int mode)
{
	char buf[20];
	char *str;

	str = "\E[6n";
	ft_bzero(buf, 20);
	ft_putstr(str);
	read(0, buf, 20);
	dprintf(2, "pos: %s\n", buf + 2);
	return (mode ? get_row(buf) : get_col(buf));
}

size_t			get_cursor_position(int mode)
{
	size_t res;

	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	res = cursor_position(mode);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	return (res);
}
