/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:52:20 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "heart.h"
# include <errno.h>

# define HEREDOC 10
# define NOTHING -1
# define FT_ASSIGN (ft_strcmp(opera->cmd[0], "ft_assign") == 0)
# define FT_HASH (ft_strcmp(opera->cmd[0], "hash") == 0)
# define FT_ENV (ft_strcmp(opera->cmd[0], "env") == 0)
# define FT_SETENV (ft_strcmp(opera->cmd[0], "setenv") == 0)
# define FT_UNSETENV (ft_strcmp(opera->cmd[0], "unsetenv") == 0)
# define FT_SET (ft_strcmp(opera->cmd[0], "set") == 0)
# define FT_EXPORT (ft_strcmp(opera->cmd[0], "export") == 0)
# define FT_UNSET (ft_strcmp(opera->cmd[0], "unset") == 0)
# define FT_CD (ft_strcmp(opera->cmd[0], "cd") == 0)
# define FT_ECHO (ft_strcmp(opera->cmd[0], "echo") == 0)
# define FT_EXIT (ft_strcmp(opera->cmd[0], "exit") == 0)

typedef struct	s_loop
{
	int			fd_in;
	int			fd_out;
	int			fd_save;
	int			start;
	char		*bin;
	int result;
}				t_loop;


void			ft_sequence(t_seq *b_seq, int fd);
void			ft_exec(t_op *opera, t_loop *loop, int pfd[3]);
int				ft_return_command(t_loop *loop);
int				isbuiltin(char *cmd, int fork);
int				ft_solver(t_op *t_exec, pid_t pid, t_loop *loop);
char			*ft_search_bin(char *cmd);
char			*ft_go_to(char *bin, int nb);
void			ft_skip(char **ttab);
void			ft_get_bin();
int				ft_builtins(t_op *t_exec);
int				ft_check_command(char *cmd);
int				ft_open_redirect(char *file, int flag, int flag2);
int				ft_return_flag(t_redirect *redirect);
int 			ft_open_redirect_builtins(char *file, int flag, int flag2);
int				ft_redirect_heredoc(t_redirect *redirect);
int				ft_check_direct_command(char *cmd);
int				ft_check_file_is_directory(char *file);
int				ft_check_source(char *source);
int				ft_return_flag2(t_op *op);
int				ft_return_fd(t_op *t_exec, int flag);
int				ft_count_pipe(t_op *tmp);
int				ft_loop_redirect(t_redirect *redirect,  int fd2, int fd_one,
				t_loop *loop);
void			ft_print_error(const char *s1, const char *s2);
int				binary_signal(int status, int pid, char *bin);
void			ft_print_message(char *source, int nb);
t_loop			ft_init_loop(int i);
char			*ft_check_command2(char *cmd);

#endif
