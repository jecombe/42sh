/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/21 21:30:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 13:43:31 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <limits.h>
# include <time.h>
# include <stdio.h>
# include <string.h>

/*
** Colors
*/

# define END "\x1b[0m"
# define BOLD "\x1b[1m"
# define UNDER "\x1b[4m"
# define REV "\x1b[7m"

# define RED "\x1b[31m"
# define YELLOW "\x1b[33m"
# define PURPLE "\x1b[35m"

char					*g_env[100];
int						g_stat;
//int						g_chevron;
char					**g_tab;

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct groupe	t_group;

typedef enum			e_type
{
	BASHOP,
	BI,
	ID,
	ARG,
	NONE
}						t_type;

typedef struct			s_read
{
	DIR					*dir;
	t_dirent			*ent;
	t_stat				stat;
	t_passwd			*user;
	t_group				*grp;
}						t_read;

typedef struct			s_token
{
	char				*id;
	t_type				type;
	char				quote;
	struct s_token		*cmdarg;
	struct s_token		*next;
}						t_token;

/*
**		MAIN - ft_minishell.c
*/

int						main(void);
void					ft_minishell(void);
void					ft_putprompt();
void					ft_handle_signal(int signo);

/*
**		ERRORS - ft_error.c
*/

int						ft_error_cd(const char *name, int stat);
int						ft_error_env(const char *name, int stat);
int						ft_error_exit(const char *name, int stat);
int						ft_error_none(const char *name);

/*
**		ENVIRONNEMENT-MANAGE - ft_env_manage.c
*/

void					ft_env_new(const char **environ);
void					ft_env_del(void);
char					*ft_getenv(const char *name);

/*
**		TREE-MANAGE - ft_tree_manage.c
*/

t_token					*ft_token_new(void);
void					ft_token_add(t_token **tbegin, t_token *element);
int						ft_token_delone(t_token **element);
void					ft_token_del(t_token *tokenlst);

/*
**		INIT - ft_init.c
*/

t_token					*ft_init(t_token *tbegin, char *cmd);

/*
**		INIT Tools - ft_init_tools.c
*/

int						ft_isquote(int c);
int						ft_isbashop(int c);
char					*ft_isbin(const char *cmd);

/*
**		LEXING - ft_lexer.c
*/

void					ft_lexer(char *cmd, char *array[100]);
void					ft_lexer_del(char *array[100]);

/*
**		SOLVING - ft_solve.c
*/

int						ft_solver(t_token *tokenlst);

/*
**		BUILT-IN CD- ft_builtin_cd.c
*/

int						ft_builtin_cd(const char *path);

/*
**		BUILT-IN ECHO- ft_builtin_echo.c
*/

int						ft_builtin_echo(char *arg[100]);

/*
**		BUILT-IN ENV - ft_builtin_env.c
*/

int						ft_builtin_env(void);
int						ft_builtin_unsetenv(const char *name);
int						ft_builtin_setenv(const char *name, const char *value);

/*
**		BUILT-IN ENV - ft_builtin_env.c
*/

int						ft_builtin_exit(t_token *token, char *arg[100]);

/*
**		BUILT-IN Tools - ft_builtin_tools.c
*/

char					*ft_builtin_join(const char *name, const char *value);

#endif
