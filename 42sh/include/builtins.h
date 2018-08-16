/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 04:28:47 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/15 05:46:29 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "./extension.h"
#include "./stdin.h"

# define PATH_MAX 4084

typedef struct	s_cd
{
	char		*home;
	char		*cwd;
	char		*oldpwd;
	char		flag;
}				t_cd;

/*
**				ft_env_tools.c
*/

char			*ft_envset_line(const char **envset, const char *name);
char			*ft_envset_value(const char **envset, const char *name);
char			*ft_envset_join(const char *name, const char *value);
int				ft_env_error(const char *prgm, const char *error);

/*
**				ft_env.c
*/

int				ft_env(t_op *exec);


int				ft_setenv(const char *name, const char *value);
int				ft_unsetenv(const char *name);
/*
**			ft_set.c
*/
/*
int			ft_set(void);
int			ft_export(const char *name, const char *value);
int			ft_unset(const char *name);
*/
#endif
