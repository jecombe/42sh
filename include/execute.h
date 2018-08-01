/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:30:44 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
#include "./parsing.h"

char			**g_bin;

void			ft_solver(t_seq *tmp_seq, char **env);
char			*ft_search_bin(char *cmd);
char			*ft_avance(char *bin);
void			ft_skip(char **ttab);
void			ft_get_bin(char **env);
int				ft_exec(t_op *tmp_op, char **env, char *bin_cmd);
void			ft_builtins(t_op *t_exec, int what);
int				ft_check_command(char *cmd);
#endif
