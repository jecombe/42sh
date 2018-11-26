/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dollar.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 00:32:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 10:50:43 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

char		*dollar_replace(char *line)
{
	char		*ret;

	ret = NULL;
	if (!(ret = ft_getenv(line, g_set)))
		ret = ft_getenv(line, g_env);
	return (ret);
}

int			dollar_end(char *str, int debut)
{
	int		i;

	i = debut;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (ft_isprint(str[i]) && !ft_isquote(str[i]) && !ft_isalnum(str[i]) &&
			str[i] != '(' && i == debut)
		i++;
	return (i > debut ? i - debut : 0);
}

int			replace_in_and_after(int k[3], char ***cmd, char **tmp, char **tmp2)
{
	char	*tmp3;
	int		len;

	len = (int)ft_strlen((*cmd)[k[0]]);
	if (k[2] + 1 + k[1] < len)
	{
		if (*tmp)
		{
			*tmp2 = ft_strsub((*cmd)[k[0]], k[2] + k[1] + 1, len - k[2] - k[1]);
			tmp3 = ft_strjoin(*tmp, *tmp2);
			ft_strdel(tmp);
			ft_strdel(tmp2);
			*tmp = ft_strdup(tmp3);
			ft_strdel(&tmp3);
		}
		else
			*tmp = ft_strsub((*cmd)[k[0]], k[2] + k[1] + 1, len - k[2] - k[1]);
	}
	if (*tmp)
	{
		ft_strreplace(cmd, k[0], *tmp);
		ft_strdel(tmp);
		return (0);
	}
	return (1);
}

int			replace_line(char ***cmd, char *line, int k[3])
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	if (k[1] > 0)
		tmp = ft_strsub((*cmd)[k[0]], 0, k[1]);
	if (line)
	{
		if (tmp)
		{
			tmp2 = ft_strjoin(tmp, line);
			ft_strdel(&tmp);
			tmp = ft_strdup(tmp2);
			ft_strdel(&tmp2);
		}
		else
			tmp = ft_strdup(line);
	}
	return (replace_in_and_after(k, cmd, &tmp, &tmp2));
}

int			ft_dollar(char ***cmd, t_bquote **i)
{
	char		*tmp;
	char		*line;
	int			k[3];

	k[0] = (*i)->i;
	k[1] = (*i)->j;
	k[2] = 0;
	line = NULL;
	tmp = NULL;
	if ((k[2] = dollar_end((*cmd)[(*i)->i], (*i)->j + 1)) >= 1)
	{
		tmp = ft_strsub((*cmd)[(*i)->i], (*i)->j + 1, k[2]);
		line = dollar_replace(tmp);
		if (replace_line(cmd, line, k))
			ft_strdel_in_tab(cmd, (*i)->i);
		if (line)
			(*i)->j = (*i)->j + (int)ft_strlen(line) - k[2];
	}
	else if (k[2] == -1)
		ft_chardel_at(&(*cmd)[(*i)->i], (*i)->j);
	else
		(*i)->j = (*i)->j + 1;
	free(line);
	free(tmp);
	return (0);
}
