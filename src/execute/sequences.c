/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sequences.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:01:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 14:43:59 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

void				ft_sequence(t_seq *b_seq, int fd)
{
	if (b_seq->token == SEMI)
	{
		while (b_seq)
		{
			//si il y a encore une separation command ==> &&
			ft_separate(b_seq, fd);
			b_seq = b_seq->next;
		}
	}
	else
	{
		//regarde si il une separation command ==> &&
		ft_separate(b_seq, fd);
	}
}
