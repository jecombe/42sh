/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:16:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 05:57:10 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXTENSION_H
# define EXTENSION_H

# include "heart.h"

typedef struct	s_bquote
{
	int			i;
	int			j;
	int			begin;
	int			dquote;
}				t_bquote;

int			extension(t_seq **b_seq);
char		**ft_split_bquote(const char *str, char *to_split);
int			ft_dollar(char ***cmd, int *i_index, int *j_index);
int			ft_manage_quote(char ***cmd, t_bquote **i);
int			extension_error(t_seq **b_seq, int ret);
int			bquote_manager(char ***cmd, t_bquote **i);
int			backslash_manager(char ***cmd, t_bquote **i);
int			ft_free_n_seq(t_seq **n_seq, t_seq **b_seq);
void		ft_free_n_op(t_op **n_op);
void		ft_free_n_redirect(t_redirect **n_redirect);
int			last_copy(char ***begin_copy, char **cmd, t_bquote *index, int ok);
void		search_index(char **begin_copy, int *i, int *j);
char		**first_copy(char **cmd, t_bquote *index, char *in_bquote, int *ok);
char		**search_prev(char **cmd, int i_max);
int			add_before_bquote(char *line, int begin, char ***cmd);
int			add_after_bquote(char *cmd, int j_index, char ***tablo, int ok);
int			manage_tild_and_dollars(char ***cmd, t_bquote **i);
int			del_nop_empty(t_op **n_op, t_op **tmp, t_op **b_op);
int			err_bquote_unmatched(e_prompt prompt);

#endif
