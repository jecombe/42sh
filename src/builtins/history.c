/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 02:27:55 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 05:02:14 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		occurence(char *little, char *big, char *old)
{
	int		i;

	i = 0;
	while (big[i] && little[i])
	{
		if (little[i] != big[i])
			return (0);
		i++;
	}
	if (old)
		return (big[i] && ft_strcmp(big, old) ? 1 : 0);
	return (big[i] ? 1 : 0);
}

static int		advanced_history_search(char **history, t_editor **ed)
{
	int			i;
	int			j;
	char		*tmp;
	int			limit;

	j = 0;
	i = 0;
	while (history[i] && j <= (*ed)->hist + 1)
	{
		limit = 0;
		tmp = made_history(history[i]);
		if ((limit = occurence((*ed)->tmp_line, tmp, (*ed)->line)) && j <= (*ed)->hist)
		{
			ft_strdel(&(*ed)->line);
			(*ed)->line = ft_strdup(tmp);
			j++;
		}
		else if (limit && UP_KEY)
		{
			(*ed)->hist = (*ed)->hist + 1;
			ft_strdel(&tmp);
			return (0);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (0);
}

static int		simple_history_search(t_editor **ed, char **history)
{
	int			i;

	i = 0;
	ft_strdel(&(*ed)->line);
	while (history[i] && i <= (*ed)->hist)
	{
		ft_strdel(&(*ed)->line);
		(*ed)->line = made_history(history[i++]);
	}
	(*ed)->hist = history[i] ? (*ed)->hist + 1 : (*ed)->hist;
	return (0);
}

void			history_get(t_editor **ed)
{
	char		**history;

	history = NULL;
	history_save(&history, NULL, 0, (char *)NULL);
	ft_reverse_tab(&history);
	if (history)
	{
		if ((*ed)->tmp_line)
		{
			advanced_history_search(history, ed);
			!(*ed)->line ? (*ed)->line = ft_strdup((*ed)->tmp_line) : 0;
		}
		else
			simple_history_search(ed, history);
	}
	ft_tabdel(&history);
}
