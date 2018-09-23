/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/23 19:15:05 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "heart.h"
# include <errno.h>

# define HEREDOC 10
# define NOTHING -1

int g_p;
int g_builtins;

typedef struct	s_loop
{
	int fd_in;
	int fd_out;
	int fd_save;
}				t_loop;

typedef struct	s_pipe
{
	int			fd_save;
	int			fd_out;
	int			fd_in;
	int			start;
	int			buil_pipe;
	char		*bin;
	int			ret;
	int			built;
}				t_pipe;

typedef struct	s_separate
{
	int			i;
	int			or_if;
	int			and_if;
	int			ret;
}				t_separate;

int				ft_solver(t_op *tmp_exec, pid_t pid, char *bin);
char			*ft_search_bin(char *cmd);
char			*ft_go_to(char *bin, int nb);
void			ft_skip(char **ttab);
void			ft_get_bin();
t_pipe			ft_init_pipe(int i);
int				ft_builtins(t_op *t_exec);
int				ft_check_command(char *cmd);
int				ft_open_redirect(char *file, int flag, int flag2);
int				ft_return_flag(t_redirect *redirect);
int 			ft_open_redirect_builtins(char *file, int flag, int flag2);
int				ft_redirect_heredoc(t_redirect *redirect, int buil);
int				ft_check_direct_command(char *cmd);
int				ft_check_file_is_directory(char *file);
int				ft_check_source(char *source);
int				ft_return_flag2(t_op *op);
int				ft_return_fd(t_op *t_exec, int flag);
void			ft_separate(t_seq *b_seq, int fd, pid_t pid);
void			ft_sequence(t_seq *b_seq, int fd, pid_t pid);
int				ft_count_pipe(t_op *tmp);
int		ft_loop_redirect(t_redirect *redirect,  int fd2, int fd_one, t_loop *loop);
void			ft_print_error(const char *s1, const char *s2);
int				binary_signal(int status, int pid, char *bin);
void			ft_print_message(char *source, int nb);
t_separate		ft_init_separate(void);
t_loop		ft_init_loop(void);
char			*ft_check_command2(char *cmd);

#endif
