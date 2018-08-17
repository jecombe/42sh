/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/14 07:27:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 02:56:37 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "../libft/include/libft.h"
# include "./stdin.h"

# define MAX_LEXER_SIZE 4096

/*
*******************************************************************************

	TOKENS :

	Global token :				260 - 265
	Control Operator :
		List terminators :		266 - 267
		List punctuation :		268 - 270
		Logical operators :		271 - 273
		Pipe operators :		274 - 275
	Redirection Operator :		276 - 284
	Reserverd Words :			285 - 300

*******************************************************************************
*/

typedef enum		e_token
{
	TOKEN = 260,
	WORD = 261,
	ASSIGNEMENT_WORD = 262,
	NAME = 263,
	NEWLINE = 264,
	IO_NUMBER = 265,

	SEMI = 266,
	AND = 267,

	DSEMI = 268,
	LPARENT = 269,
	RPARENT = 270,

	NOT = 271,
	AND_IF = 272,
	OR_IF = 273,

	PIPE = 274,
	PIPE_AND = 275,

	LESS = 276,
	LESSGREAT = 277,
	GREAT = 278,
	CLOBBER = 279,
	DGREAT = 280,
	GREATAND = 281,
	DLESS = 282,
	LESSAND = 283,
	DLESSDASH = 284,

	IF = 285,
	WHILE = 286,
	FOR = 287,
	UNTIL = 288,
	CASE = 289,
	THEN = 290,
	DO = 291,
	ESAC = 292,
	FI = 293,
	DONE = 294,
	ELIF = 295,
	ELSE = 296,

	LBRACE = 297,
	RBRACE = 298,
	BANG = 299,
	IN = 300,
}					t_token;

typedef struct		s_lex
{
	char			*name[MAX_LEXER_SIZE];
	t_token			token[MAX_LEXER_SIZE];
}					t_lex;

/*
*******************************************************************************
**						ft_lexer.c
*******************************************************************************
*/

t_lex				ft_lexer(char *input, e_prompt *prompt);

/*
*******************************************************************************
**						ft_lexer_break_words.c
*******************************************************************************
*/

int					ft_lexer_break_operator(char *input, int idx, int i);
e_prompt			ft_lexer_break_quote(char *input, int *idx);
int					ft_lexer_break_blank(char *input, int *idx, int *i);
void				ft_lexer_break_expansion(char *input, int *idx);
int					ft_lexer_break_comment(char *input, int *idx);

/*
*******************************************************************************
**						ft_lexer_utils.c
******************************************************************************
*/

char				*ft_convert_token_to_string(t_token token);
int					ft_isoperator(char *input);
int					ft_isreserved(char *input);
int					ft_isalias(char **name);
void				ft_lexer_del(t_lex *lex);

#endif
