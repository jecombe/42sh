/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 03:29:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 03:37:43 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parsing.h"

t_lex	*ft_lexer(char *input)
{
	t_lex		*begin;
	t_lex		*prev;
	t_lex		*now;
	int			i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
		}
		else if (ft_isprint(input[i]))
		{
		}
	}

	return (begin);
}

int		main(int ac, char **av)
{
	ft_lexer(av[1]);
	return (0);
}
