/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:22:07 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 21:18:56 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

char			*cut_pwd_dir(char *pwd)
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

static void		prompt_type(e_prompt prompt)
{
	if (prompt == S_QUOTE)
		ft_putstr("quote> ");
	else if (prompt == B_QUOTE)
		ft_putstr("bquote> ");
	else if (prompt == D_QUOTE)
		ft_putstr("dquote> ");
	else if (prompt == E_PIPE)
		ft_putstr("pipe> ");
	else if (prompt == E_HDOC)
		ft_putstr("heredoc> ");
	else if (prompt == DB_QUOTE)
		ft_putstr("dquote bquote> ");
}

void			display_prompt(e_prompt prompt)
{
	char	pwd[4096];
	char	*error;
	char	*home;

	home = prompt == 0 ? ft_getenv("HOME", g_env) : NULL;
	if (prompt != PROMPT)
		return (prompt_type(prompt));
	getcwd(pwd, sizeof(pwd));
	error = ft_getenv("?", g_set);
	ft_putstr(error && error[0] == '1' ? "\e[91m➜\e[0m" : "\e[92m➜\e[0m");
	ft_putstr("  \e[1m\e[93m");
	if (!ft_strcmp(pwd, !home ? "" : home))
		ft_putstr("~");
	else
		ft_putstr(cut_pwd_dir(pwd));
	ft_putstr("\e[0m ");
	ft_print_git_branch();
	ft_putstr(error && error[0] == '1' ? "\U0001F44E" : "\U0001F44D");
	ft_putstr("  ");
	free(error);
	ft_strdel(&home);
}
