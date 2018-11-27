/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:33:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 02:24:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		ft_get_shell_info(void)
{
	char	*s;
	int		i;

	s = NULL;
	i = 0;
	if (!(s = ft_envset_value((const char **)g_env, "TERM")))
		if (!(s = ft_strdup("xterm-256color")))
			return (EXIT_FAILURE);
	add_to_env("TERM", s);
	if (tgetent(NULL, s) == ERR)
		return (EXIT_FAILURE);
	ft_strdel(&s);
	if ((s = ft_envset_value((const char **)g_env, "SHLVL")))
		i = ft_atoi(s);
	ft_strdel(&s);
	if (!(s = ft_itoa(i + 1)))
		return (EXIT_FAILURE);
	add_to_env("SHLVL", s);
	ft_strdel(&s);
	add_to_env("101SH_VERSION", "21SH_PLEINS_DE_SEGFAULT");
	return (EXIT_SUCCESS);
}

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
}

static void		ft_get_file_info(const char *path)
{
	char	*tmp;

	if ((tmp = ft_strjoin(path, "/.TMPDIR")))
		add_to_env("TMPDIR", tmp);
	ft_strdel(&tmp);
	if ((tmp = ft_strjoin(path, "/101sh")))
		add_to_env("_", tmp);
	ft_strdel(&tmp);
	add_to_env("CLICOLOR", "1");
}

int				init_env(const char *path)
{
	extern char	**environ;

	if (environ)
		g_env = ft_tabdup(environ);
	if (ft_get_shell_info())
		return (EXIT_FAILURE);
	ft_get_user_info();
	ft_get_file_info(path);
	return (EXIT_SUCCESS);
}
