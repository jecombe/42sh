/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 15:41:21 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
#include "./parsing.h"
#include "./stdin.h"

char			**g_bin;

int				ft_solver(t_op *tmp_op, char **env);
char			*ft_search_bin(char *cmd);
char			*ft_avance(char *bin);
void			ft_skip(char **ttab);
void			ft_get_bin(char **env);
int				ft_exec(t_op *tmp_op, char **env, char *bin_cmd, int flag);
int				ft_builtins(t_op *t_exec, int what, int flag);
int				ft_check_command(char *cmd);
int 			ft_echo(t_op *t_exec, int flag);
int 			ft_cd(t_op *t_exec, int flag);
int 			ft_exit(t_op *t_exec, int flag);
int 			ft_env(t_op *t_exec, int flag);
int 			ft_setenv(t_op *t_exec, int flag);
int 			ft_unsetenv(t_op *t_exec, int flag);
int				ft_builtins(t_op *t_exec, int what, int flag);
void			ft_open_redirect(char *file, int flag, int flag2);
int				ft_return_flag(t_op *t_exec);
#endif
