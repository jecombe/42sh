/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 08:43:55 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/includes/libft.h"
#include "../lexer-master/lexer.h"

typedef struct					s_sc
{
	char						**cmd;//COMMANDE COMPLETE
	e_token						token;//NOT OPERATOR
}								t_sc;

typedef struct					s_cc
{
	e_token				key;//Mot cle tels que "IF" "THEN" "ELSE" "ELIF" "FI" "DO" "DONE" "CASE" "ESAC" "WHILE" "UNTIL" "FOR"
	t_sc				*sc;
	int					open;
	int					close;
	struct s_cc			*next_in;
	struct s_cc			*prev_in;
	struct s_cc			*next_out;
	struct s_cc			*prev_out;
}								t_cc;

typedef struct					s_op
{
	e_token						token;//PIPE, LOGICAL REDIRECTION OPERATOR
	t_sc						*sc;//commande sans mot cle(simple commande)
	t_cc						*cc;//commande comprenant un mot cle(commande compose)
	struct s_op					*next;//SUITE DE L'OPERATEUR
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
/*
typedef struct		s_word
{
	char			*name;
	e_token			token;
	s_word			*next;
}					t_word;

typedef struct		s_command
{
	e_token			token; // && || | ;

	struct cmd		*next;
}					t_command;

typedef struct		s_sequence
{
	e_token			token; // ; ou &
	struct s_cmd	cmd*;
	struct s_seq	*next;
}				t_sequence;
*/
