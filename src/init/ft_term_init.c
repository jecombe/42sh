/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 07:04:27 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/init.h"
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

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

int					manage_info_history(char *av)
{
	char		*str;
	char		buff[4096];
	int			fd;
	int			i;

	i = 0;
	add_to_set("HISTSIZE", "500");
	str = ft_strjoin(search_path_of_101sh(av), "/.historic");
	if (!access(str, F_OK))
	{
		add_to_set("HISTFILE", str);
		fd = open(str, O_RDONLY);
		while (get_next_line(fd, &str) > 0)
		{
			ft_strdel(&str);
			i++;
		}
		close(fd);
		str = ft_itoa(i);
		add_to_set("HISTFILESIZE", str);
	}
	else
	{
		add_to_set("HISTFILESIZE", "NULL");
		add_to_set("HISTFILE", "UNKNOW");
	}
	return (0);
}

int					get_sysname(void)
{
	struct		utsname t_utsname;
	struct stat statbuf;
	struct passwd *pwd;

	uname(&t_utsname);
	add_to_set("SYSNAME", t_utsname.sysname);
	return (0);
}

int					ft_init_set(char *av)
{
	char		buff[4096];
	char		*str;

	g_set = ft_tabdup(g_env);
	str = ft_itoa(getpid());
	add_to_set("PID", str);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(getppid());
	add_to_set("PPID", str);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(getuid());
	add_to_set("UID", str);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(geteuid());
	add_to_set("EUID", str);
	if (str)
		ft_strdel(&str);
	add_to_set("IFS", " \t\n");
	gethostname(buff, sizeof(buff));
	add_to_set("HOSTNAME", buff);
	manage_info_history(av);
	get_sysname();
	return (0);
}

int					ft_term_init(int ac, char **av)
{
	char			*term;

	if (init_env(ac, av))
		return (1);
	if (ft_init_set(av[0]))
		return (1);
	if (!(term = getenv("TERM")))
		term = "xterm-256color";
	if (tgetent(NULL, term) == ERR)
		return (1);
	return (0);
}
