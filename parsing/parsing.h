/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 02:50:26 by gmadec      ###    #+. /#+    ###.fr     */
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

enum	e_parse
{
	DLESS_ON,
	DLESS_OFF,
	DGREAT_ON,
	DGREAT_OFF,
	LESSAND_ON,
	LESSAND_OFF,
	GREATAND_ON,
	GREATAND_OFF,
};

typedef struct					s_lex
{
	char						*name[4096];
	enum e_token				token[4096];
}								t_lex;

typedef struct					s_sc
{
	char						*arg;
	enum e_token				token;
	struct s_sc					*next;//commande suivante
	struct s_sc					*prev;
}								t_sc;

typedef struct					s_cc
{
	enum e_token				key;//Mot cle tels que "IF" "THEN" "ELSE" "ELIF" "FI" "DO" "DONE" "CASE" "ESAC" "WHILE" "UNTIL" "FOR"
	t_sc						*sc;
	int							close;
	struct s_cc			*next_in;
	struct s_cc			*prev_in;
	struct s_cc			*next_out;
	struct s_cc			*prev_out;
}								t_cc;

typedef struct					s_op
{
	enum e_token				op;//Operateur de separation tels que "NONE" ">>" "<<" '<' '>' ">&" "<&" "<<-" "||" "&&"
	int							close;
	t_sc						*sc;//commande sans mot cle(simple commande)
	t_cc						*cc;//commande comprenant un mot cle(commande compose)
	struct s_op					*next;//commande suivante
	struct s_op					*prev;
}								t_op;

typedef struct					s_seq
{
	t_op						*op;
	int							close;
	struct s_seq				*next;
	struct s_seq				*prev;
}								t_seq;

t_seq							*ft_manage_parsing(t_lex lex);
t_lex							ft_lexer(char *input);
int								ft_isoperator(char *input, char c);
int								ft_lexer_break_operator(char *input, int idx, int i);
void							ft_lexer_break_quote(char *input, int *idx);
void							ft_lexer_break_expansion(char *input, int *idx);
int								ft_lexer_break_blank(char *input, int *idx, int *i);
int								ft_lexer_break_comment(char *input, int *idx);
t_seq							*ft_manage_parsing(t_lex lex);
