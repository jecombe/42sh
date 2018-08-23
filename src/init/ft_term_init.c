/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/23 08:53:20 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

/*
int					manage_info_history(char *av)
{
	char		*str;
	char		buff[4096];
	int			fd;
	int			i;

	i = 0;
	ft_malloc_cmd(&g_set, "HISTSIZE=500");
	str = ft_strjoin(search_path_of_101sh(av), "/.historic");
	if (!access(str, F_OK))
	{
		add_to_env("HISTFILE", str, &g_set);
		fd = open(str, O_RDONLY);
		while (get_next_line(fd, &str) > 0)
		{
			ft_strdel(&str);
			i++;
		}
		close(fd);
		str = ft_itoa(i);
		add_to_env("HISTFILESIZE", str, &g_set);
	}
	else
	{
		add_to_env("HISTFILESIZE", "NULL", &g_set);
		add_to_env("HISTFILE", "UNKNOW", &g_set);
	}
	return (0);
}
*/
int					ft_get_user_info()
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

int					ft_init_env(int ac, char **av)
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
/*
int					ft_init_set(char *av)
{
	char		buff[4096];
	char		*str;
	struct		utsname t_utsname;

	str = ft_itoa(getpid());
	add_to_env("PID", str, &g_set);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(getppid());
	add_to_env("PPID", str, &g_set);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(getuid());
	add_to_env("UID", str, &g_set);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(geteuid());
	add_to_env("EUID", str, &g_set);
	if (str)
		ft_strdel(&str);
	add_to_env("IFS", " \t\n", &g_set);
	gethostname(buff, sizeof(buff));
	add_to_env("HOSTNAME", buff, &g_set);
	manage_info_history(av);
	struct stat statbuf;
	struct passwd *pwd;
	uname(&t_utsname);
	add_to_env("SYSNAME", t_utsname.sysname, &g_set);
	return (0);
}
*/
int					ft_term_init(int ac, char **av)
{
	char			*term;
	int				i = -1;

	if (ft_init_env(ac, av))
		return (1);
//	if (ft_init_set(av[0]))
//		return (1);
	while (g_env[++i])
		printf("[%d]%s\n", i, g_env[i]);
	if (!(term = getenv("TERM")))
		term = "xterm-256color";
	if (tgetent(NULL, term) == ERR)
		return (1);
	return (0);
}
