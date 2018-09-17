/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sequences.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:01:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 16:41:14 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void				ft_sequence(t_seq *b_seq, int fd, pid_t pid)
{
	if (b_seq->token == SEMI)
	{
		while (b_seq)
		{
			//si il y a encore une separation command ==> &&
			ft_separate(b_seq, fd, pid);
			b_seq = b_seq->next;
		}
	}
	else
	{
		//regarde si il une separation command ==> &&
		ft_separate(b_seq, fd, pid);
	}
}
