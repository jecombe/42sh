/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:41:57 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 01:42:59 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "heart.h"

int			init_shell(int ac, const char **av);
int			init_files(const char *path);
int			init_env(const char *path);
int			init_set(int ac, const char **av);
int			init_builtins(const char *bin);

int			add_to_env(char *name, char *value);
int			add_to_set(char *name, char *value);

char		*concat_name_value(char *name, char *value);
char		*search_path_of_101sh(const char *bin);

int			index_to_var(char *name, char **env);
char		*ft_envset_line(const char **envset, const char *name);
char		*ft_envset_join(const char *name, const char *value);
char		*ft_envset_value(const char **envset, const char *name);

#endif
