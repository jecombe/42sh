/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bquote_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 07:06:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:50:55 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			err_bquote_unmatched(e_prompt prompt)
{
	if (prompt == S_QUOTE)
		ft_putendl_fd("zsh: unmatched '", 2);
	else if (prompt == D_QUOTE)
		ft_putendl_fd("zsh: unmatched \"", 2);
	else if (prompt == E_HDOC)
		ft_putendl_fd("zsh: unmatched <<", 2);
	else if (prompt == E_PIPE)
		ft_putendl_fd("zsh: unmatched |", 2);
	else if (prompt == BACKSLASH)
		ft_putendl_fd("zsh: unmatched \\", 2);
		ft_putendl_fd("zsh: parse error in command substitution", 2);
	return (1);
}

int			add_after_bquote(char *cmd, int j_index, char ***tablo, int ok)
{
	char		*tmp;
	char		*tmp2;
	int			tab_index;

	tab_index = 0;
	tmp = NULL;
	if (j_index < (int)ft_strlen(cmd))
	{
		tmp = ft_strsub(cmd, j_index, ft_strlen(cmd) - j_index);
		if (*tablo && ok)
		{
			tab_index = ft_tablen(*tablo) - 1;
			tmp2 = ft_strjoin((*tablo)[tab_index], tmp);
			ft_strdel(&(*tablo)[tab_index]);
			(*tablo)[tab_index] = ft_strdup(tmp2);
			ft_strdel(&tmp2);
		}
		else
		{
			ft_malloc_cmd(tablo, tmp);
		}
		ft_strdel(&tmp);
	}
	return (0);
}

int			add_before_bquote(char *line, int begin, char ***cmd)
{
	char		*tmp;
	char		*before_bquote;
	int			i;

	before_bquote = NULL;
	i = 0;
	tmp = NULL;
	if (begin > 0)
	{
		before_bquote = ft_strsub(line, 0, begin);
		if (*cmd)
		{
			tmp = ft_strjoin(before_bquote, (*cmd)[0]);
			ft_strdel(&(*cmd)[0]);
			(*cmd)[0] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else
			ft_malloc_cmd(cmd, before_bquote);
		ft_strdel(&before_bquote);
	}
	return (0);
}

char		**search_prev(char **cmd, int i_max)
{
	int			i;
	char		**ret;

	ret = NULL;
	i = 0;
	while (i < i_max)
	{
		if (ft_malloc_cmd(&ret, cmd[i]))
			return (NULL);
		i++;
	}
	return (ret);
}
