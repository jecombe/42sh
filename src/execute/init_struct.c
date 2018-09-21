/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 13:48:40 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 18:37:29 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

t_pipe		ft_init_pipe(int i)
{
	t_pipe tpipe;

	tpipe.fd_save = 0;
	tpipe.fd_out = 1;
	tpipe.fd_in = 0;
	tpipe.start = i;
	tpipe.buil_pipe = 0;
	tpipe.bin = NULL;
	tpipe.ret = 0;
	tpipe.built = 0;
	return (tpipe);
}


t_separate ft_init_separate(void)
{
	t_separate separate;

	separate.i = 0;
	separate.or_if = 0;
	separate.and_if = 0;
	separate.ret = 0;
	return (separate);
}
t_loop		ft_init_loop(void)
{
	t_loop	loop;

	loop.fd_in = 0;
	loop.fd_out = 1;
	loop.fd_save = 0;
	return (loop);
}
