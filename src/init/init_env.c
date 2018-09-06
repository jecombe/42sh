/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 05:33:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 09:47:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

static int				ft_get_user_info(void)
{
	char		buff[4096];
	char		*str;
	int			i = 0;

	ft_strclr(buff);
	str = NULL;
	i = 0;
//	add_to_env("PWD", getcwd(buff, sizeof(buff)));
//	if (ft_envset_exist((const char **)g_env, "PWD"))
	if (getcwd(buff, sizeof(buff)))
		ft_setenv("PWD", getcwd(buff, sizeof(buff)), 0);
	ft_strclr(buff);
//	add_to_env("SHELL", "/bin/bash");
	if (getcwd(buff, sizeof(buff)))
		ft_setenv("PWD", getcwd(buff, sizeof(buff)), 0);
	ft_strclr(buff);
	if ((str = ft_strjoin("/Users/", getlogin())))
		ft_setenv("HOME", str, 0);
//	if (str)
//		ft_strdel(&str);
	(str) ? ft_strdel(&str) : 0;
	ft_setenv("101SH_VERSION", "21SH_PLEINS_DE_SEGFAULT", 0);
	if ((str = getlogin()))
	{
		ft_setenv("USER", str, 0);
		ft_setenv("LOGNAME", str, 0);
	}
	if ((str = ft_envset_value((const char **)g_env, "SHLVL")))
	{
		i = ft_atoi(str);
		ft_strdel(&str);
		if ((str = ft_itoa(i + 1)))
			ft_setenv("SHLVL", str, 0);
		(str) ? ft_strdel(&str) : 0;
	}
	else
		ft_setenv("SHLVL", "1", 0);
	return (EXIT_SUCCESS);
}

static int			ft_get_file_info(char *path)
{
	char	*buf;

	buf = NULL;
	if (!(buf = ft_strjoin(path, "/.TMPDIR")))
		return (EXIT_FAILURE);
	ft_setenv("TMPDIR", buf, 0);
	ft_strdel(&buf);
	if (!(buf = ft_strjoin(path, "/101sh")))
		return (EXIT_FAILURE);
	ft_setenv("_", buf, 0);
	ft_strdel(&buf);
	return (EXIT_SUCCESS);
}

int					init_env(int ac, const char **av)
{
	extern char		**environ;
//	char			*tmp;
//	char			*tmp2;
	char			*path;

	path = NULL;
	if ((g_env = ft_tabdup(environ)))
		ft_unsetenv("_", 0);
	ft_get_user_info();
	if (!(index_to_var("TERM", (const char **)g_env)))
		ft_setenv("TERM", "xterm-256color", 0);
	//add_to_env("TERM", "xterm-256color");
	if (tgetent(NULL, "xterm-256color") == ERR)
		return (EXIT_FAILURE);
	if ((path = search_path_of_101sh((char *)av[0])))
		if (ft_get_file_info(path))
			return (EXIT_FAILURE);
	/*{
		tmp2 = ft_strjoin(tmp, "/.TMPDIR");
		//add_to_env("TMPDIR", tmp2);
		ft_setenv("TMPDIR", tmp2, 0);
		ft_strdel(&tmp2);
		tmp2 = ft_strjoin(tmp, "/101sh");
		//add_to_env("_", tmp2);
		ft_setenv("_", tmp2, 0);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}*/
	return (EXIT_SUCCESS);
}
