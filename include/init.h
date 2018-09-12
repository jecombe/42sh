/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:41:57 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:36:09 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "heart.h"

int			ft_term_init(int ac, char **av);
int			init_files(char *bin);
int			init_env(int ac, char **av);
int			init_set(int ac, char **av);
int			add_to_env(char *name, char *value);
int			add_to_set(char *name, char *value);

char		*concat_name_value(char *name, char *value);
char		*search_path_of_101sh(char *bin);

int			index_to_var(char *name, char **env);
char		*ft_envset_line(const char **envset, const char *name);
char		*ft_envset_join(const char *name, const char *value);
char		*ft_envset_value(const char **envset, const char *name);
void		envset_del(void);

#endif
