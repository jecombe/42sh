/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sequences.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:01:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 04:38:08 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"






/*
void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
{
	t_op *opera;
	t_separate separate;

	separate = ft_init_separate();
	opera = b_seq->op;
		while (opera)
		{
			if (opera->token == PIPE)
				if (ft_separate_pipe(&separate, &opera, pid, fd) == 101)
					return ;
			if (opera->token != PIPE)
			{
				pipe(g_fd);
				ft_separate_no_pipe(&separate, opera, pid, fd);
			}
			opera = opera->next;
		}
	return ;
	//else
	//{
		///pipe(g_fd);
		//separate.ret = ft_solver(opera, fd, pid, 0);
		//add_to_set("?", ft_itoa(separate.ret));
	//}
}
*/



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
