/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 01:55:07 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
#include "parsing.h"

char			**g_bin;

void			ft_solver(t_op *tmp_op, char **env);
char			*ft_search_bin(char *cmd);
char			*ft_avance(char *bin);
void			ft_skip_n(char **tab);
void			ft_get_bin(char **env);
int				ft_exec(t_op *tmp_op, char **env, char *bin_cmd);
#endif
