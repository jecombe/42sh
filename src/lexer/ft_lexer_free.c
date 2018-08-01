/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer_free.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 02:17:49 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:20:17 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	ft_lexer_free(t_lex *lex)
{
	int	i;

	i = -1;
	while (lex->name[++i] && i < 4096)
		ft_strdel(&lex->name[i]);
	while (lex->token[++i] && i < 4096)
		lex->token[i] = 0;
	lex->error = '\0';
}
