/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:16:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 00:18:23 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXTENSION_H
# define EXTENSION_H

#include "./parsing.h"

char		**g_set;

int			extension(t_seq **b_seq);
int			ft_dollar(char **cmd, int *j);

#endif
