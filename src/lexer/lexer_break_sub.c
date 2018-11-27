/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_break_sub.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/25 09:54:34 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 13:21:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void			ft_lexer_break_sub(char *input, int *idx)
{
	char	c;

	c = input[*idx];
	if (c == '(')
		while (input[++(*idx)])
			if (input[*idx] == '\0' || (input[(*idx)] == ')' &&
						(*idx == 0 || input[*idx - 1] == '\\')))
				break ;
}
