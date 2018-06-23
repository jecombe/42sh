/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/23 11:49:10 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/includes/libft.h"

enum	e_token
{
	/*RESERVED_WORD*/
	NEWLINE,/*\n*///0
	AND_IF,/*&&*///1
	OR_IF,/*||*///2
	DSEMI,/*;;*///3
	DLESS,/*<<*///4
	DGREAT,/*>>*///5
	LESSAND,/*<&*///6
	GREATAND,/*>&*///7
	LESSGREAT,/*<>*///8
	DLESSDASH,/*<<-*///9
	CLOBBER,/*>|*///10
	IF,/*if*///11
	THEN,/*then*///12
	ELSE,/*else*///13
	ELIF,/*elif*///14
	FI,/*fi*///15
	DO,/*do*///16
	DONE,/*done*///17
	CASE,/*case*///18
	ESAC,/*esac*///19
	WHILE,/*while*///20
	UNTIL,/*until*///21
	FOR,/*for*///22
	LBRACE,/*{*///23
	RBRACE,/*}*///24
	BANG,/*!*///25
	IN,/*in*///26
	PIPE,/*|*///27
	SEMI,/*;*///28
	AND,/*&*///29
	SLESS,/*<*///30
	SGREAT,/*>*///31
	WORD,/**///32
	NUL//38
};

typedef struct	s_cmd t_cmd;

typedef struct		s_lex
{
	char					*name[4096];
	enum e_token			token[4096];
}					t_lex;

typedef struct	s_simplecmd
{
	char				*arg;
	enum e_token		token;
	struct s_arg		*next;//commande suivante
	struct s_arg		*prev;
}				t_simplecmd;

typedef struct	s_composecmd
{
	enum e_token		mot_cle;//Mot cle tels que "IF" "THEN" "ELSE" "ELIF" "FI" "DO" "DONE" "CASE" "ESAC" "WHILE" "UNTIL" "FOR"
	t_simplecmd				*scmd;
	typedef struct s_composecmd	*next_in;
	typedef struct s_composecmd	*prev_in;
}				t_composecmd;

struct	s_cmd
{
	enum e_token		operateur;//Operateur de separation tels que "NONE" ">>" "<<" '<' '>' ">&" "<&" "<<-" "||" "&&"
	t_simplecmd			*simplecmd;//commande sans mot cle
	t_composecmd		*compose_cmd;//commande comprenant un mot cle
	struct s_cmd		*next;//commande suivante
	struct s_cmd		*prev;
};

typedef struct	s_seq
{
	t_cmd				*cmd;
	struct s_seq		*next;
	struct s_seq		*prev;
}				t_seq;

void		ft_parsing(t_lex lex);
t_lex		ft_lexer(char *input);
int			ft_isoperator(char *input, char c);
int			ft_lexer_break_operator(char *input, int idx, int i);
void		ft_lexer_break_quote(char *input, int *idx);
void		ft_lexer_break_expansion(char *input, int *idx);
int			ft_lexer_break_blank(char *input, int *idx, int *i);
int			ft_lexer_break_comment(char *input, int *idx);
