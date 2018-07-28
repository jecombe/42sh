/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 05:11:33 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/include/libft.h"
#include "./lexer.h"

typedef struct					s_op
{
	e_token						token[2];// token >= DSEMI && token <= DLESSDASH POUR TOKEN[0] ET SI IL Y A UN TOKEN DIFFERENT D'UNE REDIRECTION ALORS TOKEN[1] PEUT ETRE UNE REDIRECTION
	char						**cmd;//COMMANDE COMPLETE
	struct s_op					*next;//COMMANDE SUIVANT L'OPERATEUR
	struct s_op					*prev;
}								t_op;

typedef struct					s_seq
{
	e_token						token; // LIST TERMINATOR
	t_op						*op;
	struct s_seq				*next;
	struct s_seq				*prev;
}								t_seq;

t_seq							*ft_manage_parsing(t_lex lex);
