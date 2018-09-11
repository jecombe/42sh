/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:14:20 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/07 04:42:32 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

const int		equal_to_split(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

const size_t	ft_wordcount_b_quote(const char *s, char *c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			while (s[i] && equal_to_split(s[i], c))
				i++;
			while (s[i] && !equal_to_split(s[i], c))
			{
				if (equal_to_split(s[i + 1], c) || !(s[i + 1]))
					count++;
				i++;
			}
		}
	}
	return (count);
}

const size_t	ft_wordlen_bquote(const char *s, char *c, size_t i)
{
	size_t	count;

	count = 0;
	if (s)
	{
		while (!equal_to_split(s[i], c) && s[i] != '\0')
		{
			count++;
			i++;
		}
	}
	return (count);
}

char			**ft_split_bquote(const char *str, char *to_split)
{
	char	**tablo;
	size_t	w;
	size_t	i;
	int		v;

	i = 0;
	if (!(str))
		return (NULL);
	w = ft_wordcount_b_quote(str, to_split);
	if (!(tablo = (char **)malloc(sizeof(char *) * (w + 1))))
		return (NULL);
	v = 0;
	while (str[i] != '\0')
	{
		while (equal_to_split(str[i], to_split))
			i++;
		if (str[i] != '\0')
		{
			tablo[v++] = ft_strsub(str, ((int)i),
			ft_wordlen_bquote(str, to_split, i));
			i += ft_wordlen_bquote(str, to_split, i);
		}
	}
	tablo[v] = (NULL);
	return (tablo);
}
