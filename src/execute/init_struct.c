/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 13:48:40 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/23 20:47:48 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

t_loop		ft_init_loop(int i)
{
	t_loop	loop;

	loop.fd_in = 0;
	loop.fd_out = 1;
	loop.fd_save = 0;
	loop.start = i;
	loop.bin = NULL;
	return (loop);
}
