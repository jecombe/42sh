/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/22 07:41:15 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/includes/libft.h"

typedef enum	s_token
{
	/*RESERVED_WORD*/
	NEWLINE,//0
	AND_IF,//1
	OR_IF,//2
	DSEMI,//3
	DLESS,//4
	DGREAT,//5
	LESSAND,//6
	GREATAND,//7
	LESSGREAT,//8
	DLESSDASH,//9
	CLOBBER,//10
	IF,//11
	THEN,//12
	ELSE,//13
	ELIF,//14
	FI,//15
	DO,//16
	DONE,//17
	CASE,//18
	ESAC,//19
	WHILE,//20
	UNTIL,//21
	FOR,//22
	LBRACE,//23
	RBRACE,//24
	BANG,//25
	IN,//26
	PIPE,//27
	SEMI,//28
	AND,//29
	SLESS,//30
	SGREAT,//31
	WORD,//32
	NUL//38
}				e_token;

typedef struct		s_lex
{
	char			*name[4096];
	e_token			token[4096];
}					t_lex;

typedef struct	s_arg
{
	char				*name;
	e_token				token;
	struct s_arg		*next;//commande suivante
	struct s_arg		*prev;
}				t_arg;

typedef struct	s_cmd
{
	t_arg				*arg;//1 iere argument le binaire et la suite les args
	struct s_cmd		*next;//commande suivante
	struct s_cmd		*prev;
}				t_cmd;

typedef struct	s_seq
{
	t_cmd				*cmd;
	struct s_seq		*next;// ';' '||' '&&'
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
