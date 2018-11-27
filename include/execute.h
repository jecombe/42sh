/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 11:58:44 by jecombe     ###    #+. /#+    ###.fr     */
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
# define FT_READ (ft_strcmp(opera->cmd[0], "read") == 0)

int g_h;
int g_error_bquote;

typedef struct	s_loop
{
	int			fd_in;
	int			fd_out;
	int			fd_save;
	char		*bin;
	int			result;
	int			exit;
	pid_t		pid;
	int			error_redir_nb;
}				t_loop;

int				ft_sequence(t_seq *b_seq, int fd, t_loop *loop);
int				ft_exec(t_op *opera, t_loop *loop, int pfd[3], int fd2);
int				ft_return_command(t_loop *loop);
int				isbuiltin(char *cmd);
char			*ft_search_bin(char *cmd);
int				ft_builtins(t_op *t_exec, t_loop *loop);
int				ft_open_redirect(char *file, int flag, int flag2);
int				ft_return_flag(t_redirect *redirect);
int				ft_open_redirect_builtins(char *file, int flag, int flag2);
int				ft_redirect_heredoc(t_redirect *redirect);
int				ft_check_direct_command(char *cmd);
int				ft_check_file_is_directory(const char *file);
int				ft_check_source(char *source);
int				ft_return_fd(t_op *t_exec, int flag);
int				ft_loop_redirect(t_redirect *redirect, int fd2, int fd_one,
		t_loop *loop);
void			ft_print_error(const char *s1, const char *s2);
int				binary_signal(int status, int pid, char *bin);
int				ft_print_message(char *source, int nb);
void			ft_save_fd(int fd_org[3]);
void			ft_restore_fd(int fd_org[3]);
void			ft_loop_reset(t_loop *loop);
int				ft_check_file_is_regular(const char *file);
int				ft_check_file_is_regular2(const char *file);
void			ft_solve(t_op *opera, t_loop *loop, int pfd[2]);
int				ft_command_not_found(t_op *opera, t_loop *loop);
void			ft_message_random(void);
int				init_parcour_tab(t_bquote **i);
int				return_parcour_tab(char **cmd, int ret, t_bquote **i);
int				ft_check_permission(char *source);

#endif
