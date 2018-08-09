/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_search_dyn.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 01:01:54 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 05:11:28 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_search_line(char *str, int i)
{
	char	*ret;
	int		j = i;
	int		back = 0;

	if (str[j] == ' ' || str[j] == '\0')
	{
		if (j == 0)
			return (NULL);
		if (str[j - 1] == ' ' || str[j - 1] == '`' || str[j - 1] == '|' ||
		str[j - 1] == ';' || str[j - 1] == '&')
			return (NULL);
		while (j > 0 && back == 0)
		{
			if (str[j] == '`' || str[j] == ';' || str[j] == '|' ||
			str[j] == '&')
				j > 0 ? back = 1 : j--;
			else
				j--;
		}
		ret = ft_strsub(str, j, i);
		return (ret);
	}
	else
		return (NULL);
}

char		*ft_ret_word(char *str)
{
	char	*ret;
	int		i;

	i = ft_strlen(str);
	ret = NULL;
	while (i >= 0)
	{
		if (str[i] == ' ' || str[i] == '|' || str[i] == '&' || str[i] == ';'
		|| str[i] == '`')
		{
			i++;
			return (ft_strdup(str + i));
		}
		else
			i--;
	}
	i = i == -1 ? 0 : i;
	ret = ft_strdup(str + i);
	return (ret);
}

int			ft_search_mod(t_tline *tline, char **ret, int i, int w)
{
	char	*actual;

	i = tline->x_instr;
	actual = ft_search_line(tline->tmp ? tline->tmp : tline->actual, i);
	if (actual)
	{
		i = 0;
		if ((actual[i] == '`' || actual[i] == '&' || actual[i] == ';' ||
		actual[i] == '|') && actual[i + 1])
			i++;
		while (actual[i])
		{
			if (actual[i] >= '!' && actual[i] <= '~')
			{
				while (actual[i] > ' ' && actual[i] <= '~' && actual[i])
					i++;
				w++;
			}
			else
				i++;
		}
		actual ? *ret = ft_ret_word(actual) : 0;
		return (w > 1 ? 0 : 1);
	}
	return (101);
}

void		ft_manage_search(t_tline **tline, char **my_env)
{
	int		ret;
	char	*str;
	int			i;
	int			w;

	w = 0;
	i = 0;
	str = NULL;
	if ((ret = ft_search_mod(*tline, &str, i, w)) == 1)
		ft_manage_sdsearch_soft(&(*tline), my_env, &str);
	else if (ret == 0)
		ft_manage_sdsearch_file(&(*tline), my_env, &str);
	else
	{
		if (str)
			ft_strdel(&str);
		if ((*tline)->searchdyn)
			ft_strdel(&(*tline)->searchdyn);
	}
}

void		ft_search_dyn(t_tline **tline, char **my_env)
{
	if ((*tline)->x_instr == (*tline)->x_max && my_env)
	{
		if (ft_getenv("SEARCH_DYN", my_env))
			if (ft_strcmp(ft_getenv("SEARCH_DYN", my_env), "ON") == 0)
			{
				ft_putstr(LIGHT_GREY);
				if ((*tline)->actual || (*tline)->tmp)
					ft_manage_search(&(*tline), my_env);
				else if ((*tline)->searchdyn)
					ft_strdel(&(*tline)->searchdyn);
				ft_putstr(END);
			}
	}
	else if ((*tline)->searchdyn)
		ft_strdel(&(*tline)->searchdyn);
}
