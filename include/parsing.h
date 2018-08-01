/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 01:50:29 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

t_seq							*ft_parsing(t_lex lex);
int								ft_parse_error(e_token token);
void							ft_free_b_seq(t_seq **b_seq);
void							ft_free_b_op(t_op **b_op);
void							ft_free_b_redirect(t_redirect **b_redirect);
t_redirect						*ft_malloc_redirect(void);
t_op							*ft_malloc_op(void);
t_seq							*ft_malloc_seq(void);
int								ft_attrib_last_redirect(t_op **n_op, t_redirect **n_redirect);
int								ft_attrib_last_op(t_seq **b_seq, t_op **ret_op);
int								ft_attrib_last_seq(t_seq **b_seq, t_seq **n_seq);
int								ft_attrib_next_redirect(t_redirect **n_redirect);
int								ft_attrib_next_op(t_op **n_op);
int								ft_manage_seq(t_seq **b_seq, e_token token);
int								ft_manage_logical_and_pipe(t_seq **b_seq, e_token token);
int								ft_manage_redirection(t_seq **b_seq, e_token token, char *name);
int								ft_manage_word(t_seq **b_seq, char *name);
int								ft_manage_io_number(t_seq **b_seq, char *name);
void							ft_convert_token(char **str, e_token token);
#endif
