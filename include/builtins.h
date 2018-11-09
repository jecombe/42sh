/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 04:28:47 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 07:36:44 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "heart.h"

# define DO_NOTHING (void)0

typedef struct			s_read
{
	char				*line;
	char				*prompt;
	char				delimiter;
	int					limit;
	int					hide;
	int					backs;
	int					split;
	char				*vars[100];
	int					fd;
	int					secs;
	int					interactive;
}						t_read;

typedef enum			e_bierror
{
	NOBIERROR,
	BIFLAG,
	BINOFOUND,
	BITOMANY,
	BITOFEW,
	BIEQUAL,
	BINUM
}						t_bierror;

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

int						ft_bierrors(const char *prgm, const char *cmd,
		t_bierror err);

/*
*******************************************************************************
**					ft_env.c
*******************************************************************************
*/

int						ft_env(t_op *exec);

/*
*******************************************************************************
**					ft_set_unset_env.c
*******************************************************************************
*/

int						ft_setenv(const char *name, const char *value);
int						ft_unsetenv(const char *name);

/*
*******************************************************************************
**					ft_env_tools.c
*******************************************************************************
*/

char					*ft_get_var(char *line);
char					*ft_get_value(char *line);
char					*ft_envset_line(const char **envset, const char *name);
char					*ft_envset_value(const char **envset, const char *name);
char					*ft_envset_join(const char *name, const char *value);

/*
*******************************************************************************
**					set.c
*******************************************************************************
*/

int						set(t_op *exec);

/*
*******************************************************************************
**					export.c
*******************************************************************************
*/

int						ft_export(t_op *exec);

/*
*******************************************************************************
**					unset.c
*******************************************************************************
*/

int						unset(t_op *exec);
int						ft_unset_var(char *cmd);

/*
*******************************************************************************
**					ft_cd.c
*******************************************************************************
*/

int						ft_change_dir(char **cmd);

/*
*******************************************************************************
**					ft_echo.c
*******************************************************************************
*/

int						ft_echo(t_op *t_exec);

/*
*******************************************************************************
**					ft_exit.c
*******************************************************************************
*/

int						ft_exit(t_op *t_exec);

/*
*******************************************************************************
**					ft_hash.c
*******************************************************************************
*/

void					ft_hashtable(char *cmd, char *raccmd);
int						ft_hash(const char *cmd);
void					ft_hash_print(t_hashtable *hashtable);

/*
*******************************************************************************
**					ft_hash_utils.c
*******************************************************************************
*/
void					hash_clear(void);
t_hashtable				*ft_hashtable_create(void);
t_hashcase				*ft_create_case(const char *cmd, const char *raccmd);
void					ft_save_hash(t_hashtable **hashtable);
void					ft_hash_add(t_hashcase **begin, t_hashcase *hashcase);
void					history_save(char ***history, char *news, int version,
		char *s);
void					history_get(t_shell *sh, char key[]);

/*
*******************************************************************************
**					ft_read_utils.c
*******************************************************************************
*/
void					ft_init_read(t_read *rd);
void					ft_split_to_array(t_read *rd);
void					ft_read_str_escape(char **s);
void					ft_read_add_to_set(t_read *rd);

/*
*******************************************************************************
**					ft_read.c
*******************************************************************************
*/
void					ft_read_input(t_read *rd);
int						ft_read_options_long(t_read *rd, char letter,
		char *arg);
void					ft_read_parse_vars(t_read *rd, char **cmd);
int						ft_read_options(t_read *rd, char **cmd, int i, int j);
void					ft_read(char **cmd);

#endif
