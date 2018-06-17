/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:39:56 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/19 19:02:28 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	int		ft_count_letters(char const *s, char c, size_t i)
{
	size_t count_letters;

	count_letters = 0;
	while (s[i] != c && s[i])
	{
		count_letters++;
		i++;
	}
	return (count_letters);
}

static int		ft_count_words(char const *s, char c)
{
	int		i;
	int		word_counter;

	word_counter = 0;
	i = 0;
	if (s[i] != c)
		word_counter++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			word_counter++;
		i++;
	}
	return (word_counter);
}

char			**ft_strsplit(char const *s, char c)
{
	int		j;
	int		k;
	int		index;
	char	**words;

	j = 0;
	index = -1;
	if (s == NULL)
		return (NULL);
	if (!(words = (char**)malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	while (s[++index])
		if (s[index] != c && s[index])
		{
			k = 0;
			if (!(words[j] = (char*)malloc(sizeof(char) *
							(ft_count_letters(s, c, index) + 1))))
				return (NULL);
			while (s[index] != c && s[index])
				words[j][k++] = s[index++];
			index--;
			words[j++][k] = '\0';
		}
	words[j] = NULL;
	return (words);
}
