/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 04:28:47 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/16 05:44:43 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "heart.h"

typedef enum	e_bierror
{
	NOBIERROR,
	BIFLAG,
	BINOFOUND,
	BITOMANY,
	BITOFEW,
	BIEQUAL
}				t_bierror;

typedef struct			s_hashcase
{
	int					hits;
	char				*command;
	char				*raccmd;
	struct s_hashcase	*next;
}						t_hashcase;

typedef struct			s_hashtable
{
	int					key;
	t_hashcase			*hashcase;
}						t_hashtable;

typedef struct			s_history
{
	char	**cmd;
}						t_history;

/*
*******************************************************************************
**					builtins_errors.c
*******************************************************************************
*/

int				ft_bierrors(const char *prgm, const char *cmd, t_bierror err, int fd_open);

/*
*******************************************************************************
**					ft_env.c
*******************************************************************************
*/

int				ft_env(t_op *exec, int fd_open, int p);

/*
*******************************************************************************
**					ft_set_unset_env.c
*******************************************************************************
*/

int				ft_setenv(const char *name, const char *value, int fd_open);
int				ft_unsetenv(const char *name, int fd_open);

/*
*******************************************************************************
**					ft_env_tools.c
*******************************************************************************
*/

char			*ft_get_var(char *line);
char			*ft_get_value(char *line);
char			*ft_envset_line(const char **envset, const char *name);
char			*ft_envset_value(const char **envset, const char *name);
char			*ft_envset_join(const char *name, const char *value);

/*
*******************************************************************************
**					set.c
*******************************************************************************
*/

int				set(t_op *exec, int p, int fd_open);

/*
*******************************************************************************
**					export.c
*******************************************************************************
*/

int				ft_export(t_op *exec, int fd_open);

/*
*******************************************************************************
**					ft_assign.c
*******************************************************************************
*/

int				ft_assign(t_op *exec);

/*
*******************************************************************************
**					unset.c
*******************************************************************************
*/

int				unset(t_op *exec, int fd_open);
int				ft_unset_var(char *cmd);

/*
*******************************************************************************
**					ft_cd.c
*******************************************************************************
*/

int				ft_cd(t_op *t_exec, int flag, int fd, int p);

/*
*******************************************************************************
**					ft_cd_utils.c
*******************************************************************************
*/

int				ft_canonical(char **curpath);
int				ft_rules(char **cmd);

/*
*******************************************************************************
**					ft_echo.c
*******************************************************************************
*/

int				ft_echo(t_op *t_exec, int flag, int fd, int p);

/*
*******************************************************************************
**					ft_exit.c
*******************************************************************************
*/

int				ft_exit(t_op *t_exec, int flag, int fd_open);

/*
*******************************************************************************
					ft_hash.c
*******************************************************************************
*/

void			ft_hashtable(char *cmd, char *raccmd);
int				ft_hash(const char *cmd);
void			ft_hash_print(t_hashtable *hashtable);

/*
*******************************************************************************
					ft_hash_utils.c
*******************************************************************************
*/

t_hashtable		*ft_hashtable_create(void);
t_hashcase		*ft_create_case(const char *cmd, const char *raccmd);
void			ft_save_hash(t_hashtable **hashtable);
void			ft_hash_add(t_hashcase **begin, t_hashcase *hashcase);
void			history_save(char ***history, char *news, int version, char *s);
void			history_get(char **line, int index);

#endif
