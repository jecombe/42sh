/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 05:41:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>

typedef enum	s_quote
{
	NQUOTE,
	QUOTE,
	BQUOTE,
	DQUOTE
}				e_quote;

typedef enum	s_sep
{
	NSEP,
	PIPE,
	SINF,
	DINF,
	SSUP,
	DSUP
}				e_sep;

typedef enum	s_seqtype
{
	NTYPE,
	SHELLTYPE
}
				e_seqtype;

typedef struct	s_arg
{
	char				*name;
	e_quote				quote;
	struct s_arg		*next;//commande suivante
	struct s_arg		*prev;
}				t_arg;

typedef struct	s_cmd
{
	t_arg				*arg;//1 iere argument le binaire et la suite les args
	e_sep				sep_next;
	e_sep				sep_prev;
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
