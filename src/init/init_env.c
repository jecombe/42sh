/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:33:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:25:42 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		ft_get_user_info(void)
{
	char	buff[BUFF_SIZE];
	char	*str;
	int		i;

	ft_bzero(buff, BUFF_SIZE);
	str = NULL;
	i = 0;
	if ((getcwd(buff, sizeof(buff))))
		add_to_env("PWD", buff);
	add_to_env("SHELL", "/bin/bash");
	if ((str = getlogin()))
	{
		ft_strcpy(buff, str);
		add_to_env("USER", str);
		add_to_env("LOGNAME", str);
		ft_strdel(&str);
		(str = ft_strjoin("/Users/", buff)) ? add_to_env("HOME", str) : 0;
		ft_strdel(&str);
	}
	add_to_env("101SH_VERSION", "21SH_PLEINS_DE_SEGFAULT");
	if ((str = ft_getenv("SHLVL", g_env)))
		i = ft_atoi(str);
	ft_strdel(&str);
	(str = ft_itoa(i + 1)) ? add_to_env("SHLVL", str) : 0;
	ft_strdel(&str);
}

static void		ft_get_file_info(const char *bin)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	if ((path = search_path_of_101sh(bin)))
	{
		if ((tmp = ft_strjoin(path, "/.TMPDIR")))
			add_to_env("TMPDIR", tmp);
		ft_strdel(&tmp);
		if ((tmp = ft_strjoin(path, "/101sh")))
			add_to_env("_", tmp);
		ft_strdel(&tmp);
		ft_strdel(&path);
	}
}

int				init_env(const char **av)
{
	extern char	**environ;
	char		*s;

	s = NULL;
	if (environ)
		g_env = ft_tabdup(environ);
	ft_get_user_info();
	if (!(s = ft_envset_value((const char **)g_env, "TERM")))
		if ((s = ft_strdup("xterm-256color")))
			add_to_env("TERM", s);
	if (tgetent(NULL, s) == ERR)
		return (EXIT_FAILURE);
	ft_strdel(&s);
	ft_get_file_info(av[0]);
	return (EXIT_SUCCESS);
}
