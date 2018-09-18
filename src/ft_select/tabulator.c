/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 07:31:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		add_word(t_editor **ed, char **word, int *count, int *i)
{
	int		j;

	*count = *count + 1;
	return (0);
}

int		search_word(char **word, t_editor **ed)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if ((*ed)->line)
	{
		while ((*ed)->line[i] && i < (int)(*ed)->cursor_str_pos)
		{
			if ((i == 0 && ft_istab((*ed)->line[i])) ||
			(i > 0 && ft_isblank((*ed)->line[i - 1]) && ft_istab((*ed)->line[i])))
				add_word(ed, word, &count, &i);
			else
				i++;
		}
		return (count > 0 && ft_isblank((*ed)->line[i - 1]) ? count + 1 : count);
	}
	return (-2);
}

int		tabulator(t_editor **ed)
{
	int		nb_word;
	char	*word;

	word = NULL;
	if ((nb_word = search_word(&word, ed)) > -1)
	{
		if (nb_word == 1)
		{
			printf("SEARCH BIN\n");
		}
		else if (nb_word)
			printf("SEARCH IN REP\n");
	}
	printf("LINE == %s NB_WORD == %d\n", (*ed)->line, nb_word);
	sleep(2);
	return (0);
}
