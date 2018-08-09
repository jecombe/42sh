/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_concat_param.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/09 03:45:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 04:18:14 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		ft_word_size(char **av)
{
	int i;
	int j;
	int size;

	i = 0;
	size = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			j++;
			size++;
		}
		size++;
		i++;
	}
	return (size);
}

char	*ft_concat_param(char **av)
{
	int word_size;
	char *word;
	int i;
	int j;
	int k;

	word_size = ft_word_size(av) + 1;
	i = -1;
	k = 0;
	if (!(word = (char*)malloc(sizeof(char) * word_size)))
		return (NULL);
	word[word_size - 1] = '\0';
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
			word[k++] = av[i][j++];
		word[k++] = '\n';
	}
	return (word);
}

int		main(int ac, char **av)
{
	char *word;

	word = NULL;
	if (ac >= 2)
	{
		word = ft_concat_param(av + 1);
		printf("%s", word);
	}
	free(word);
//	sleep(150);
}
