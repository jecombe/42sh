/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 04:59:29 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "heart.h"

# define HEREDOC 10
# define NOTHING -1


int				g_fd[2];

int g_input;
int g_output;
int g_save;
int g_start;
int g_c;

typedef struct	s_loop
{
	int			fd;
	int			i;
	int			flag;
	int			flag2;
	int			error;
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

int				ft_solver(t_op *tmp_exec, int fd, pid_t pid, int save, int *fdd, int input, int ouput);
char			*ft_search_bin(char *cmd);
char			*ft_go_to(char *bin, int nb);
void			ft_skip(char **ttab);
void			ft_get_bin();
t_pipe			ft_init_pipe(int i);
int				ft_exec(t_op *tmp_op, char *bin_cmd, int fd, pid_t pid);
int				ft_builtins(t_op *t_exec, int what, int flag, int fd);
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
int				ft_pipe(t_op *opera, int co, int fd2);
int				ft_count_pipe(t_op *tmp);
int				ft_loop_redirect(t_redirect *redirect, int buil, int fd2, int before_pipe);
void			ft_print_error(const char *s1, const char *s2);
int				binary_signal(int status, int pid, char *bin);
void			ft_print_message(char *source, int nb);
t_loop			ft_init_loop(void);
t_separate		ft_init_separate(void);
int				ft_prelim_loop(t_op *exec, int fd, int std_err);
int				ft_loop_redirect2(t_redirect *redirect,  int fd2, int  ouput, int save, int input, int *fdd);
void			ft_exec2(t_op *tmp_op, char *bin_cmd, int fd, pid_t pid);

#endif
