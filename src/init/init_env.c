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

int			ft_unsetenv(const char *name, int fd_open)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_env, name)))
		return (EXIT_SUCCESS);
	env = ft_tabdup(g_env);
	ft_tabdel(&g_env);
	g_env = NULL;
	while (env[++i])
		if (!(ft_strcmp(env[i], s) == 0))
			ft_malloc_cmd(&g_env, env[i]);
	ft_tabdel(&env);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}

char		*ft_envset_value(const char **envset, const char *name)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	tmp = NULL;
	s = NULL;
	while (envset[++i])
	{
		tmp = ft_strsub(envset[i], 0, ft_strlen(name));
		if (ft_strcmp(name, tmp) == 0 && envset[i][ft_strlen(name)] == '=')
			s = ft_strdup(ft_strchr(envset[i], '=') + 1);
		ft_strdel(&tmp);
		if (s)
			break ;
	}
	return (s);
}

char		*ft_envset_line(const char **envset, const char *name)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	tmp = NULL;
	s = NULL;
	while (envset[++i])
	{
		tmp = ft_strsub(envset[i], 0, ft_strlen(name));
		if (ft_strcmp(name, tmp) == 0 && envset[i][ft_strlen(name)] == '=')
			s = ft_strdup(envset[i]);
		ft_strdel(&tmp);
		if (s)
			break ;
	}
	return (s);
}
char		*ft_envset_join(const char *name, const char *value)
{
	char	*tmp;
	char	*s;

	tmp = NULL;
	s = NULL;
	tmp = ft_strjoin(name, "=");
	if (value)
		s = ft_strjoin(tmp, value);
	else
		s = ft_strjoin(tmp, "''");
	ft_strdel(&tmp);
	return (s);
}
int			ft_setenv(const char *name, const char *value, int fd_open)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_env, name)))
		ft_malloc_cmd(&g_env, (s = ft_envset_join(name, value)));
	else
	{
		while (g_env[++i])
			if ((ft_strcmp(g_env[i], s)) == 0)
				break ;
		ft_strdel(&g_env[i]);
		g_env[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}

int			ft_envset_exist(const char **envset, const char *name)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (envset[++i])
	{
		if (!(tmp = ft_strsub(envset[i], 0, ft_strlen(name))))
			return (EXIT_FAILURE);
		if ((ft_strcmp(name, tmp) == 0) && (envset[i][ft_strlen(name)] == '='))
			break ;
		ft_strdel(&tmp);
	}
	(tmp) ? ft_strdel(&tmp) : 0;
	if (!envset[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
	ft_setenv("PWD", getcwd(buff, sizeof(buff)), 0);
//	add_to_env("SHELL", "/bin/bash");
	ft_setenv("PWD", getcwd(buff, sizeof(buff)), 0);
	if ((str = ft_strjoin("/Users/", getlogin())))
		ft_setenv("HOME", str, 0);
//	if (str)
//		ft_strdel(&str);
	(str) ? ft_strdel(&str) : 0;
	ft_setenv("101SH_VERSION", "21SH_PLEINS_DE_SEGFAULT", 0);
	ft_setenv("USER", getlogin(), 0);
	ft_setenv("LOGNAME", getlogin(), 0);
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
