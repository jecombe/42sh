/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:22:07 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/02 19:39:12 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** pwd = Path Working Directory
** rwd = Real Working Directory
*/

char	*cut_pwd_dir(char *pwd)
{
	int i;

	i = ft_strlen(pwd);
	if (pwd[0] == '/' && i == 1)
		return (pwd);
	while (i >= 0)
	{
		if (pwd[i] == '/')
			return (pwd + i + 1);
		i--;
	}
	return (0);
}

void	display_prompt(char *pwd, char *home, int err, char *rwd)
{
	g_prompt_size = 1;
	err == 2 ? ft_putstr(RED) : ft_putstr(WHITE);
	ft_putstr("101sh");
	ft_putstr(END);
	ft_putchar(' ');
	ft_putstr(BLUE);
	if (ft_strcmp(pwd, !home ? "" : home) == 0)
	{
		ft_putstr("~");
		g_prompt_size++;
	}
	else if (ft_strlen(pwd) == (ft_strlen(rwd) + 1))
	{
			ft_putstr(pwd);
			g_prompt_size += ft_strlen(pwd);
	}
	else
	{
		ft_putstr(rwd);
		g_prompt_size += ft_strlen(rwd);
	}
	ft_putstr(END);
	ft_putchar(' ');
	g_prompt_size += 7;
}
