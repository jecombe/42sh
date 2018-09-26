/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sequences.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:01:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 16:45:58 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void				ft_sequence(t_seq *b_seq, int fd, pid_t pid)
{
	t_seq *seq;

	seq = b_seq;
	while (seq)
	{
		ft_separate(seq, fd, pid);
		seq = seq->next;
	}
}
