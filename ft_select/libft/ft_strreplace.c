/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strreplace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/20 14:55:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/24 16:16:14 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void		ft_norme1(int i[], int word[], char *str, char *at_replace)
{
	while (str[i[0]])
	{
		i[3] = 0;
		while (str[i[0] + i[3]] == at_replace[i[3]] && i[4] < i[6] && str[i[0] +
		i[3]] && i[3] < (int)ft_strlen(at_replace))
			i[3]++;
		if (i[3] == (int)ft_strlen(at_replace))
		{
			word[i[4]] = i[0];
			i[4]++;
		}
		i[0] = i[3] == 0 ? i[0] + 1 : i[0] + i[3];
	}
}

static char		*ft_norme3(int i[], char *str, char **tab)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (int)ft_strlen(str) -
	((i[4] * (int)ft_strlen(tab[0]))) + ((i[4] * (int)ft_strlen(tab[1]))) + 1);
	i[0] = 0;
	i[1] = 0;
	i[5] = 0;
	return (tmp);
}

static char		*ft_norme2(char *str, int i[], int word[], char **tab)
{
	char	*tmp;

	tmp = ft_norme3(i, str, tab);
	while (str[i[0]])
	{
		i[3] = 0;
		i[2] = 0;
		if (i[1] < i[4] && (i[0] - (word[i[1]]) < 0 ? -word[i[1]] :
		word[i[1]]) == word[i[1]])
		{
			while (tab[1][i[2]])
			{
				tmp[i[5] + i[2]] = tab[1][i[2]];
				i[2]++;
			}
			i[1]++;
		}
		else
			tmp[i[5]] = str[i[0]];
		i[5] += i[2] > 0 ? i[2] : 1;
		i[0] += i[2] > 0 ? ft_strlen(tab[0]) : 1;
	}
	tmp[i[5]] = '\0';
	ft_tabdel(&tab);
	return (tmp);
}

static char		**ft_2strtotab(char *str1, char *str2)
{
	char		**tab;

	tab = malloc(sizeof(char*) * 2 + 1);
	tab[2] = NULL;
	tab[0] = ft_strdup(str1);
	tab[1] = ft_strdup(str2);
	return (tab);
}

char			*ft_strreplace(char *str, char *at_replace, char *bye, int nb)
{
	int		i[7];
	char	*tmp;
	int		word[nb];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	i[4] = 0;
	i[5] = 0;
	i[6] = nb;
	if (i[6] <= 0)
		return (i[6] < 0 ? 0 : str);
	ft_norme1(i, word, str, at_replace);
	tmp = ft_norme2(str, i, word, ft_2strtotab(at_replace, bye));
	return (tmp);
}
