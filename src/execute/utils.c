/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:25:35 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 01:45:30 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void		ft_skip_n(char **tab)
{
	int i = 1;
	int t = 0;
	while (tab[i])
	{
		while (tab[i][t])
		{
			if (tab[i][t] == '\n')
			{
				tab[i][t] = '\0';
				t = 0;
			}
			t++;
		}
		i++;
	}
}

char	*ft_avance(char *bin)
{
	bin++;
	bin++;
	bin++;
	bin++;
	bin++;
	return (bin);

}
