/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dollar.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 00:32:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/26 14:21:58 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"
#include "../../include/builtins.h"

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
	while (str[i] && !ft_isquote(str[i]) && !ft_isblank(str[i]) && str[i] != '\\' && str[i] != '$')
		i++;
	return (i > debut ? i - debut : i);
}

int			replace_line(char ***cmd, int *i, int *j, char *line, int at)
{
	int		len;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	if (*j > 0)
		tmp = ft_strsub((*cmd)[*i], 0, *j);
	len = (int)ft_strlen((*cmd)[*i]) - 1;
	if (line)
	{
		if (tmp)
		{
			tmp2 = ft_strjoin(tmp, line);
			ft_strdel(&tmp);
			tmp = ft_strdup(tmp2);
	//		ft_strdel(&tmp2);
		}
		else
			tmp = ft_strdup(line);
	}
	if (at + 1 + *j < len)
	{
		if (tmp)
		{
			tmp2 = ft_strsub((*cmd)[*i], at + *j + 1, len - at - *j + 1);
			tmp3 = ft_strjoin(tmp, tmp2);
			ft_strdel(&tmp);
			ft_strdel(&tmp2);
			tmp = ft_strdup(tmp3);
			ft_strdel(&tmp3);
		}
		else
			tmp = ft_strsub((*cmd)[*i], at + *j + 1, len - at - *j);
	}
	if (tmp)
	{
		ft_strdel(&(*cmd)[*i]);
		(*cmd)[*i] = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (0);
	}
	else
		return (1);
}

int			ft_dollar(char ***cmd, int *i, int *j)
{
	char		*tmp;
	char		*line;
	int			at;
	char		**ret;
	int			tablo[2];

	ret = NULL;
	if ((at = dollar_end((*cmd)[*i], *j + 1)) >= 1)
	{
		tmp = ft_strsub((*cmd)[*i], *j + 1, at);
		line = dollar_replace(tmp);
		if(replace_line(cmd, i, j, line, at))
			ft_strdel_in_tab(cmd, *i);
		if (line)
			*j = *j + (int)ft_strlen(line);
	}
	else
		*j = *j + 1;
	return (0);
}
