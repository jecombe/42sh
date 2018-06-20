/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 03:29:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 05:05:43 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parsing.h"


e_token ft_isoperator(char c)
{
	e_token token;

	return (token);
}

void	ft_quoting(char input)
{
	/*
	 *
	if (c == '\')
	{sofjdowfjw
	}

	* */
}

t_lex	*ft_lexer(char *input)
{
	t_lex		*begin;
	t_lex		*prev;
	t_lex		*now;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i <= (int)ft_strlen(input))
	{
		if (input[i] == '\0')
		{
		}
		else if (i > 0)
		{
			j = i - 1;
			if (ft_isoperator(i) && input - 1)
			{
			}
			else if (!ft_isoperator(i) && input -1)
			{
			}
		}
		if (input[i] == '\\' || input[i] == '"' || input[i] == '\'')
		{
			ft_quoting(input[i]);
		}
		else if (input[i] == '$' || input[i] == '`')
		{
		}
		else if (ft_isoperator(input[i]))
		{
		}
		else if (input[i] == '\\' && input[i + 1] == 'n')
		{
		}
		else if (ft_isblank(input[i]))
		{
			//PAS FINI
			i++;
			j = i;
		}
		else if (ft_isprint(input[i - 1]))
		{
			ft_putchar(input[i++]);
		}
		else
			j = i;
	}
	return (begin);
}

int		main(int ac, char **av)
{
//	t_lex *lex;
	
//	lex;
	ft_lexer(av[1]);
	return (0);
}
