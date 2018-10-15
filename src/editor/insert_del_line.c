/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_del_line.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 20:32:55 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 20:33:12 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		del_lines(int nb_line)
{
	int		i;

	i = nb_line;
	while (i > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("dl", NULL), 1, ft_putchar);
		i--;
	}
	tputs(tgetstr("up", NULL), 1, ft_putchar);
}

void		insert_lines(int nb_line)
{
	int		i;

	i = nb_line;
	while (i > 0)
	{
		tputs(tgetstr("al", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		i--;
	}
}
