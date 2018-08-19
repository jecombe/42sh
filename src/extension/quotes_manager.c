/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quotes_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 06:05:00 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/19 02:31:17 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

char		*ft_replace_dquote(char *str, int *j)
{
	char		*ret;
	int			j_tmp;
	int			j_tmp2;

	j_tmp = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	while (j_tmp < *j)
	{
		ret[j_tmp] = str[j_tmp];
		j_tmp++;
	}
	j_tmp2 = *j + 1;
	if (str[j_tmp2])
		while (str[j_tmp2])
			ret[j_tmp++] = str[j_tmp2++];
	ret[j_tmp] = '\0';
	printf("RET == %s\n", ret);
	return (ret);
}

char		*ft_replace_quote(char *str, int *j)
{
	char		*ret;
	int			j_tmp;
	int			j_tmp2;

	j_tmp = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) - 1));
	while (j_tmp < *j)
	{
		ret[j_tmp] = str[j_tmp];
		j_tmp++;
	}
	while (str[*j + 1] != '\'')
	{
		ret[j_tmp++] = str[*j + 1];
		*j += 1;
	}
	j_tmp2 = *j + 2;
	while (str[j_tmp2])
		ret[j_tmp++] = str[j_tmp2++];
	ret[j_tmp] = '\0';
	return (ret);
}

int			ft_manage_quote(char ***tablo, int i, int *j, char* (*f)(char*, int*))
{
	char		*tmp;

	if ((ft_strlen((*tablo)[i]) > 1 && (*tablo)[i][*j] == '"') || ft_strlen((*tablo)[i]) > 2)
	{
		tmp = f((*tablo)[i], j);
		ft_strdel(&(*tablo)[i]);
		(*tablo)[i] = ft_strdup(tmp);
	}
	else
	{
		printf("I == %d\n", i);
		printf("STRDEL_IN_TAB\n");
		*j = 0;
		if (ft_strdel_in_tab(&(*tablo), i))
			return (1);
		//ft_strdel_in_tab(&(*tablo), *j);
	}
	return (0);
}
