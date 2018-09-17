/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_token.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 06:54:28 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:40:52 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

char		*ft_search_simple_token(t_token token)
{
	if (token == TOKEN)
		return (ft_strdup("TOKEN"));
	else if (token == WORD)
		return (ft_strdup("WORD"));
	else if (token == ASSIGNEMENT_WORD)
		return (ft_strdup("ASSIGNEMENT_WORD"));
	else if (token == NAME)
		return (ft_strdup("NAME"));
	else if (token == NEWLINE)
		return (ft_strdup("NEWLINE"));
	else
		return (ft_strdup("IO_NUMBER"));
}

char		*ft_search_control_operateur(t_token token)
{
	if (token == SEMI)
		return (ft_strdup("SEMI"));
	else if (token == AND)
		return (ft_strdup("AND"));
	else if (token == DSEMI)
		return (ft_strdup("DSEMI"));
	else if (token == LPARENT)
		return (ft_strdup("LPARENT"));
	else if (token == RPARENT)
		return (ft_strdup("RPARENT"));
	else if (token == NOT)
		return (ft_strdup("NOT"));
	else if (token == AND_IF)
		return (ft_strdup("AND_IF"));
	else if (token == OR_IF)
		return (ft_strdup("OR_IF"));
	else if (token == PIPE)
		return (ft_strdup("PIPE"));
	else
		return (ft_strdup("PIPE_AND"));
}

char		*ft_search_redirection_operator(t_token token)
{
	if (token == LESS)
		return (ft_strdup("LESS"));
	else if (token == LESSGREAT)
		return (ft_strdup("LESSGREAT"));
	else if (token == GREAT)
		return (ft_strdup("GREAT"));
	else if (token == CLOBBER)
		return (ft_strdup("CLOBBER"));
	else if (token == DGREAT)
		return (ft_strdup("DGREAT"));
	else if (token == GREATAND)
		return (ft_strdup("GREATAND"));
	else if (token == DLESS)
		return (ft_strdup("DLESS"));
	else if (token == LESSAND)
		return (ft_strdup("LESSAND"));
	else
		return (ft_strdup("DLESSDASH"));
}

char		*ft_search_reserved_word(t_token token)
{
	if (token == LBRACE)
		return (ft_strdup("LBRACE"));
	else if (token == RBRACE)
		return (ft_strdup("RBRACE"));
	else if (token == BANG)
		return (ft_strdup("BANG"));
	else
		return (ft_strdup("IN"));
}

void		ft_convert_token(char **str, t_token token)
{
	if (token >= TOKEN && token <= IO_NUMBER)
		*str = ft_search_simple_token(token);
	else if (token >= SEMI && token <= PIPE_AND)
		*str = ft_search_control_operateur(token);
	else if (token >= LESS && token <= DLESSDASH)
		*str = ft_search_redirection_operator(token);
	else if (token >= LBRACE && token <= IN)
		*str = ft_search_reserved_word(token);
}
