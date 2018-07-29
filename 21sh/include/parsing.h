/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/29 04:23:29 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/include/libft.h"
#include "./lexer.h"

typedef struct					s_redirect
{
	char						*fd;
	e_token						redirect;//< << > >> >| >& <& <<
	char						*file;
	struct s_redirect			*next;
	struct s_redirect			*prev;
}								t_redirect;

typedef struct					s_op
{
	char						**cmd;//COMMANDE COMPLETE
	t_redirect					*redirect;
	e_token						token;//| |& || &&
	struct s_op					*next;//COMMANDE SUIVANT L'OPERATEUR
	struct s_op					*prev;
}								t_op;

typedef struct					s_seq
{
	e_token						token;//LIST TERMINATOR
	t_op						*op;
	struct s_seq				*next;
	struct s_seq				*prev;
}								t_seq;

t_seq							*ft_manage_parsing(t_lex lex);
