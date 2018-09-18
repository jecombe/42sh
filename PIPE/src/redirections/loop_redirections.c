/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/17 04:11:44 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 04:36:20 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"
/*
int		ft_loop_redirect2(t_redirect *redirect,  int fd2, int  ouput, int save, int input, int *fdd)
{
	int file;
	int flag;

	flag = 0;
	file = -1;
	while (redirect)
	{
		if (redirect->redirect == DLESS)
			g_input = ft_redirect_heredoc(redirect, 0);
		if (redirect->redirect == GREAT || redirect->redirect == DGREAT)
		{
			flag = ft_return_flag(redirect);
			g_output = ft_open_redirect(redirect->file ,flag, O_WRONLY);
		}
		if (redirect->redirect == LESS)
		{
			if (ft_check_source(redirect->file) == -1)
			{
				ft_print_message(redirect->file, 2);
				return (EXIT_FAILURE);
			}
			g_input = ft_open_redirect(redirect->file, O_RDONLY, 0);
		}
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}*/
