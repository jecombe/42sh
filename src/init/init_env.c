/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:33:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 12:22:38 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/init.h"

static int				ft_get_user_info(void)
{
	char		buff[4096];
	char		*str;
	int			i = 0;

	add_to_env("PWD", getcwd(buff, sizeof(buff)));
	add_to_env("SHELL", "/bin/bash");
	if ((str = ft_strjoin("/Users/", getlogin())))
		add_to_env("HOME", str);
	if (str)
		ft_strdel(&str);
	add_to_env("101SH_VERSION", "21SH_PLEINS_DE_SEGFAULT");
	add_to_env("USER", getlogin());
	add_to_env("LOGNAME", getlogin());
	if ((str = ft_getenv("SHLVL", g_env)))
	{
		i = ft_atoi(str);
		ft_strdel(&str);
		if ((str = ft_itoa(i + 1)))
		{
			add_to_env("SHLVL", str);
			ft_strdel(&str);
		}
	}
	else
		add_to_env("SHLVL", "1");
	return (0);
}

int					init_env(int ac, char **av)
{
	char			*tmp;
	char			*tmp2;
	extern char		**environ;

	tmp = NULL;
	g_env = ft_tabdup(environ);
	ft_get_user_info();
	if ((tmp = search_path_of_101sh(av[0])))
	{
		tmp2 = ft_strjoin(tmp, "/.TMPDIR");
		add_to_env("TMPDIR", tmp2);
		ft_strdel(&tmp2);
		tmp2 = ft_strjoin(tmp, "/101sh");
		add_to_env("_", tmp2);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (0);
}
