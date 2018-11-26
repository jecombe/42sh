/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:22:07 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 12:37:18 by gmadec      ###    #+. /#+    ###.fr     */
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

static char			*ft_get_current_dir(void)
{
	char	*pwd;
	char	cwd[2048];

	if (!(pwd = ft_getenv("PWD", g_env)))
	{
		getcwd(cwd, sizeof(cwd));
		pwd = ft_strdup(cwd);
	}
	return (pwd);
}

static int			geo_prompt(t_prompt prompt)
{
	char	*pwd;
	char	*err;
	char	*home;
	char	buff[2048];
	int		ret;

	ft_bzero(buff, sizeof(buff));
	home = prompt == 0 ? ft_getenv("HOME", g_env) : NULL;
	if (prompt != PROMPT)
		return (0);
	pwd = ft_get_current_dir();
	err = ft_getenv("?", g_set);
	ft_geoprintf(buff, err && err[0] == '0' ? "\e[92m➜\e[0m" : "\e[91m➜\e[0m");
	ft_geoprintf(buff, "  \033[01;93m");
	if (!ft_strcmp(pwd, !home ? "" : home))
		ft_geoprintf(buff, "~%s", "\e[0m ");
	else
		ft_geoprintf(buff, "%s%s", cut_pwd_dir(pwd), "\e[0m ");
	ret = 14 + ft_strlen(cut_pwd_dir(pwd)) + ft_get_git_branch(buff);
	ft_geoprintf(buff, err && err[0] == '0' ? "\U0001F44D  " : "\U0001F44E  ");
	free(err);
	ft_strdel(&pwd);
	ft_strdel(&home);
	ft_putstr(buff);
	return (ret);
}

int					display_prompt(t_prompt prompt)
{
	if (prompt == PROMPT)
		return (geo_prompt(prompt));
	else if (prompt == B_QUOTE || prompt == S_QUOTE)
		return (prompt == B_QUOTE ? ft_putstr("bquote> ") :
				ft_putstr("quote> "));
	else if (prompt == D_QUOTE || prompt == DB_QUOTE)
		return (prompt == D_QUOTE ? ft_putstr("dquote> ") :
				ft_putstr("dbquote> "));
	else if (prompt == E_HDOC || prompt == E_PIPE)
		return (prompt == E_HDOC ? ft_putstr("heredoc> ") :
				ft_putstr("pipe> "));
	else if (prompt == BACKSLASH)
		return (ft_putstr("bslash> "));
	else if (prompt == ORIF)
		return (ft_putstr("cmdor> "));
	else if (prompt == ANDIF)
		return (ft_putstr("cmdand> "));
	else if (prompt == SUBST)
		return (ft_putstr("cmdsubst> "));
	else
		return (0);
}
