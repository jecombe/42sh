/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:25:35 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 12:05:49 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void			ft_print_error(const char *s1, const char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

int				ft_print_message(char *source, int nb)
{
	if (nb == -1)
		ft_print_error(source, "is a directory!");
	else if (nb == -2)
		ft_print_error(source, "permission denied!");
	else if (nb == -3)
		ft_print_error(source, "no such file or directory!");
	else if (nb == -4)
		ft_print_error(source, "ambigus redirect!");
	return (EXIT_FAILURE);
}

void			ft_message_random(void)
{
	static int	number = 0;
	static char	*messages[] = {"I hate corrector", "Why are you so stupid?!",
		"What is this...? Amateur hour!?", "Are you even trying?!", "Boooo!",
		"ERROR_INCOMPETENT_USER", "Y u no speak computer???",
		"error code 1D10T", "Bad.", "¯\\_(ツ)_/¯",
		"This is why nobody likes you", "Come on! You can do it!",
		"Perhaps computer is not for you...",
		"So, I'm just going to go ahead and run rm -rf / for you.", "Nice try.",
		"This not a search engine.", "lol", "Pathetic",
		"Typing incorrect commands, eh?", "lol... plz", NULL};

	ft_putstr_color(messages[number++], 9, 1);
	if (number == ft_tablen(messages))
		number = 0;
}

int				ft_command_not_found(t_op *opera, t_loop *loop)
{
	if (opera->token != PIPE)
	{
		ft_putstr_fd("\n", 1);
		ft_message_random();
		ft_putstr_fd(STOP, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\n", 1);
	}
	ft_print_error(opera->cmd[0], "Command not found !");
	ft_putstr("\007");
	loop->result = -1;
	return (EXIT_FAILURE);
}
