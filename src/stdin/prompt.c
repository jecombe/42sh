/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:22:07 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/31 23:34:57 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

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

void		prompt_type(e_prompt prompt)
{
	if (prompt == S_QUOTE)
		ft_putstr("quote>");
	else if (prompt == B_QUOTE)
		ft_putstr("bquote>");
	else if (prompt == D_QUOTE)
		ft_putstr("dquote>");
	else if (prompt == E_PIPE)
		ft_putstr("pipe>");
	else if (prompt == E_HDOC)
		ft_putstr("heredoc>");
}

void	display_prompt(char *home, e_prompt prompt)
{
	char pwd[4096];

	if (prompt != PROMPT)
		return (prompt_type(prompt));
	getcwd(pwd, sizeof(pwd));
	//err == 2 ? ft_putstr(RED) : ft_putstr(WHITE);
	ft_putstr(WHITE);
	ft_putstr("101sh");
	ft_putstr(END);
	ft_putchar(' ');
	ft_putstr(BLUE);
	if (!ft_strcmp(pwd, !home ? "" : home))
		ft_putstr("~");
	else if (ft_strlen(pwd) == (ft_strlen(cut_pwd_dir(pwd)) + 1))
			ft_putstr(pwd);
	else
		ft_putstr(cut_pwd_dir(pwd));
	ft_putstr(END);
	ft_putchar(' ');
	if (home)
		ft_strdel(&home);
}
