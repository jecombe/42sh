/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/20 08:34:01 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 08:52:25 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int main(int ac, char **av)
{
	char **test;

	(void)ac;
	if ((test = ft_tabsplit(av[1])))
	{
		int i = 0;
		while (test[i])
		{
			printf("TEST[%d] == %s\n", i, test[i]);
			i++;
		}
	}
	return (0);
}
