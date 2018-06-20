/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 03:37:14 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/includes/libft.h"

typedef enum	s_token
{
	/*RESERVED_WORD*/
	NEWLINE,
	AND_IF,
	OR_IF,
	DSEMI,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,
	IF,
	THEN,
	ELSE,
	ELIF,
	FI,
	DO,
	DONE,
	CASE,
	ESAC,
	WHILE,
	UNTIL,
	FOR,
	LBRACE,
	RBRACE,
	BANG,
	IN,
	PIPE,
	SEMI,
	AND,
	SLESS,
	SGREAT,
/**/
	NQUOTE,
	QUOTE,
	BQUOTE,
	DQUOTE,
	NSEP,
}				e_token;

typedef struct		s_lex
{
	char			*name;
	e_token			token;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

typedef enum	s_seqtype
{
	NTYPE,
	SHELLTYPE
}
				e_seqtype;

typedef struct	s_arg
{
	char				*name;
	e_token				quote;
	struct s_arg		*next;//commande suivante
	struct s_arg		*prev;
}				t_arg;

typedef struct	s_cmd
{
	t_arg				*arg;//1 iere argument le binaire et la suite les args
	e_token				sep_next;
	e_token				sep_prev;
	struct s_cmd		*next;//commande suivante
	struct s_cmd		*prev;
}				t_cmd;

typedef struct	s_seq
{
	t_cmd				*cmd;
	e_seqtype			seqtype;
	struct s_seq		*next;// ';' '||' '&&
	struct s_seq		*prev;
}				t_seq;
