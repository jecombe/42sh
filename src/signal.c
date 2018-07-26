/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 22:39:45 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 01:59:55 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	myhandler_interrupt(int signal)
{

	if (signal == SIGINT)
	{
	}
}

void	myhandler_winsize_change(int signal)
{
	if (signal == SIGWINCH)
	{

	}
}
