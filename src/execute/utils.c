/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:25:35 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:01:20 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void		ft_skip(char **ttab)
{
	int i = 1;
	int t = 0;
	while (ttab[i])
	{
		while (ttab[i][t])
		{
			if (ttab[i][t] == '\n')
			{
				ttab[i][t] = '\0';
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
