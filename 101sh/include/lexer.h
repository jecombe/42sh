/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/14 07:27:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 09:38:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "../libft/include/libft.h"

# define MAX_TAB_SIZE 4096

typedef enum	s_token
{
	TOKEN = 260,		// TOKEN
	WORD = 261,
	ASSIGNEMENT_WORD = 262,
	NAME = 263,
	NEWLINE = 264,
	IO_NUMBER = 265,

/* CONTROL OPERATOR */
	/* List terminators */
	SEMI = 266,			// ;
	AND = 267,			// &

	/* Logical operators */
	AND_IF = 268,		// &&
	OR_IF = 269,		// ||
	NOT = 270,			// !

	/* Pipe operators */
	PIPE = 271,			// |
	PIPE_AND = 272,		// |& (shorthand for '2>&1 |')

	/* List punctuation */
	DSEMI = 273,		// ;;
	LPARENT = 274,		// (
	RPARENT = 275,		// )

/* REDIRECTION OPERATORS */
	LESS = 276,			// <
	LESSGREAT = 277,	// <>
	GREAT = 278,		// >
	CLOBBER = 279,		// >|
	DGREAT = 280,		// >>
	GREATAND = 281,		// >&
	DLESS = 282,		// <<
	LESSAND = 283,		// <&
	DLESSDASH = 284,	// <<-

/* RESERVED WORDS */
	IF = 285,
	WHILE = 286,
	FOR = 287,
	CASE = 288,
	THEN = 289,
	DO = 290,
	ESAC = 291,
	FI = 292,
	DONE = 293,
	ELIF = 294,
	ELSE = 295,
	UNTIL = 296,

	/* Not operators tokens, recognized when reserved word */
	LBRACE = 297,		// {
	RBRACE = 298,		// }
	BANG = 299,			// !
	IN = 300,			// in
}				e_token;

typedef struct		s_lex
{
	char			*name[MAX_TAB_SIZE];
	e_token			token[MAX_TAB_SIZE];
}					t_lex;

/*
**		ft_lexer.c
*/

t_lex		ft_lexer(char *input);

/*
**		ft_lexer_break_words.c
*/

int			ft_lexer_break_operator(char *input, int idx, int i);
void		ft_lexer_break_quote(char *input, int *idx);
int			ft_lexer_break_blank(char *input, int *idx, int *i);
void		ft_lexer_break_expansion(char *input, int *idx);
int			ft_lexer_break_comment(char *input, int *idx);

/*
**		ft_lexer_break_tokens.c
*/

e_token		ft_lexer_token_rules(t_lex *lex);

/*
**		ft_lexer_utils.c
*/

char		*ft_convert_token_to_string(e_token token);
int			ft_isoperator(char *input);
int			ft_isreserved(char *input);


#endif
