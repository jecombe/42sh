/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_parcour_tab.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 05:34:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 10:32:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	replace_parcour(int *ret, char ***cmd, t_bquote **i)
{
	if (!(*ret = backslash_manager(&(*cmd), i)))
		if (!(*ret = ft_manage_quote(cmd, i)))
			*ret = manage_tild_and_dollars(cmd, i);
}

int		init_parcour_tab(t_bquote **i)
{
	if (!(*i = malloc(sizeof(t_bquote))))
		return (1);
	(*i)->begin = 0;
	(*i)->i = -1;
	(*i)->j = 0;
	(*i)->dquote = 0;
	return (0);
}

int		return_parcour_tab(char **cmd, int ret, t_bquote **i)
{
	if (*i)
		free(*i);
	if (!cmd || !cmd[0])
		return (2);
	return (ret == -1 || g_interupt == 1 ? 1 : 0);
}

void	init_extension(t_token *tk, int *v_if, t_seq **b_seq, t_seq **n_seq)
{
	*tk = TOKEN;
	*v_if = 0;
	*n_seq = *b_seq;
}
