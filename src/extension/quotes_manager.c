/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quotes_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 06:05:00 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 04:59:14 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static char		*ft_replace_dquote(char *str, int *j, int *i)
{
	char		*ret;
	int			j_tmp;
	int			j_tmp2;

	(void)*i;
	j_tmp = 0;
	if (!(ret = malloc(sizeof(char) * ft_strlen(str))))
		return (NULL);
	while (j_tmp < *j)
	{
		ret[j_tmp] = str[j_tmp];
		j_tmp++;
	}
	j_tmp2 = *j + 1;
	while (str[j_tmp2])
		ret[j_tmp++] = str[j_tmp2++];
	ret[j_tmp] = '\0';
	return (ret);
}

static char		*ft_replace_quote(char *str, int *j, int *i)
{
	char		*ret;
	int			j_tmp;
	int			j_tmp2;

	j_tmp = -1;
	ret = NULL;
	if ((*i == 0 && *j == 0 && str[1] && str[2]) || *i != 0 || *j != 0)
	{
		if (!(ret = malloc(sizeof(char) * (ft_strlen(str)))))
			return (NULL);
		while (++j_tmp < *j)
			ret[j_tmp] = str[j_tmp];
		while (str[*j] && str[*j + 1] && str[*j + 1] != '\'')
		{
			ret[j_tmp++] = str[*j + 1];
			*j += 1;
		}
		j_tmp2 = *j + 2;
		while (str[j_tmp2 - 1] && str[j_tmp2])
			ret[j_tmp++] = str[j_tmp2++];
		ret[j_tmp] = '\0';
	}
	return (ret);
}

static int		manage_dsquotes(char ***tablo, t_bquote **i,
		char *(*f)(char*, int*, int*))
{
	char		*tmp;

	if (ft_strlen((*tablo)[(*i)->i]) > 1)
	{
		tmp = f((*tablo)[(*i)->i], &(*i)->j, &(*i)->i);
		ft_strdel(&(*tablo)[(*i)->i]);
		if (tmp)
			(*tablo)[(*i)->i] = ft_strdup(tmp);
		else
		{
			ft_strdel_in_tab(tablo, (*i)->i);
			return (0);
		}
		ft_strdel(&tmp);
	}
	else
		ft_strdel_in_tab(&(*tablo), (*i)->j + 1);
	return (0);
}

int				ft_manage_quote(char ***cmd, t_bquote **i)
{
	if ((*cmd)[(*i)->i][(*i)->j] == '\'' && !(*i)->dquote && !(*i)->begin)
	{
		manage_dsquotes(&(*cmd), &(*i), ft_replace_quote);
		return (1);
	}
	else if ((*cmd)[(*i)->i][(*i)->j] == '"' && !(*i)->begin)
	{
		manage_dsquotes(&(*cmd), &(*i), ft_replace_dquote);
		(*i)->dquote = (*i)->dquote == 1 ? 0 : 1;
		return (1);
	}
	else if ((*cmd)[(*i)->i][(*i)->j] == '`')
	{
		if ((*i)->begin == 0)
			(*i)->begin = (*i)->j++ == 0 ? -1 : (*i)->j - 1;
		else
		{
			(*i)->begin = (*i)->begin == -1 ? 0 : (*i)->begin;
			if (bquote_manager(&(*cmd), &(*i)) == 1)
				return (-1);
			(*i)->begin = 0;
		}
		return (1);
	}
	return (0);
}
