/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:22:07 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 16:29:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static char			*cut_pwd_dir(char *pwd)
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

static int			geo_prompt(t_prompt prompt)
{
	char	pwd[4096];
	char	*err;
	char	*home;
	char	buff[2048];
	int		ret;

	ft_bzero(buff, sizeof(buff));
	home = prompt == 0 ? ft_getenv("HOME", g_env) : NULL;
	if (prompt != PROMPT)
		return (0);
	getcwd(pwd, sizeof(pwd));
	err = ft_getenv("?", g_set);
	ft_geoprintf(buff, err && err[0] == '1' ? "\e[91m➜\e[0m" : "\e[92m➜\e[0m");
	ft_geoprintf(buff, "  \033[01;36m");
	if (!ft_strcmp(pwd, !home ? "" : home))
		ft_geoprintf(buff, "~");
	else
		ft_geoprintf(buff, cut_pwd_dir(pwd));
	ft_geoprintf(buff, "\e[0m ");
	ret = 14 + ft_strlen(cut_pwd_dir(pwd)) + ft_get_git_branch(buff);
	ft_geoprintf(buff, err && err[0] == '1' ? "\U0001F44E  " : "\U0001F44D  ");
	free(err);
	ft_strdel(&home);
	ft_putstr(buff);
	return (ret);
}

int					display_prompt(t_prompt prompt)
{
	if (prompt == PROMPT)
		return (geo_prompt(prompt));
	else if (prompt == B_QUOTE || prompt == S_QUOTE)
	{
		prompt == B_QUOTE ? ft_putstr("bquote> ") : ft_putstr("quote> ");
		return (prompt == B_QUOTE ? 8 : 7);
	}
	else if (prompt == D_QUOTE || prompt == DB_QUOTE)
	{
		prompt == D_QUOTE ? ft_putstr("dquote> ") : ft_putstr("dbquote> ");
		return (prompt == D_QUOTE ? 8 : 9);
	}
	else if (prompt == E_HDOC || prompt == E_PIPE)
	{
		prompt == E_HDOC ? ft_putstr("heredoc> ") : ft_putstr("pipe> ");
		return (prompt == E_HDOC ? 9 : 6);
	}
	else if (prompt == BACKSLASH)
	{
		ft_putstr("bslash> ");
		return (8);
	}
	else
		return (0);
}
