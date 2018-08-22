/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 07:15:20 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

int					add_to_env(char *name, char *value, int globale)
{
	int		i = 0;
	int		j;
	int		find = 0;
	char		*str;
	char		*str2;

	str = NULL;
	str2 = NULL;
	if (!(name && value))
		return (0);
	str2 = ft_strjoin(name, "=");
	str = ft_strjoin(str, value);
	printf("%s=%s\t%s\n", name, value, "env");
	if (g_env[i])
	{
		while (g_env[i] && find == 0)
		{
			j = 1;
			while (g_env[i][j] && g_env[i][j] != '=' && find == 0)
			{
				if (!ft_strncmp(g_env[i], name, j))
				{
					ft_strdel(&g_env[i]);
					g_env[i] = ft_strdup(str);
					find = 1;
				}
				j++;
			}
			i++;
		}
	}/*
	if (!find)
	{
		if (!ft_strcmp(name, "_"))
		{
		}
		else
			ft_malloc_cmd(&g_env, );
	}*/
	return (0);
}

int					manage_info_history(void)
{
	char		*str;
	char		buff[4096];
	int			fd;
	int			i;

	i = 0;
	ft_malloc_cmd(&g_set, "HISTSIZE=500");
	str = ft_strjoin(getcwd(buff, sizeof(buff)), "/.historic");
	if (!access(str, F_OK))
	{
		add_to_env("HISTFILE", str, 0);
		fd = open(str, O_RDONLY);
		while (get_next_line(fd, &str) > 0)
		{
			ft_strdel(&str);
			i++;
		}
		close(fd);
		str = ft_itoa(i);
		add_to_env("HISTFILESIZE", str, 0);
	}
	else
	{
		add_to_env("HISTFILESIZE", "NULL", 0);
		add_to_env("HISTFILE", "UNKNOW", 0);
	}
	return (0);
}

int					ft_get_user_info()
{
	char		buff[4096];
	char		*str;
	int			i = 0;

	add_to_env("PWD", getcwd(buff, sizeof(buff)), 0);
	add_to_env("SHELL", "/bin/bash", 0);
	add_to_env("HOME=/Users/", getlogin(), 0);
	add_to_env("101SH_VERSION", "21SH_PLEINS_DE_SEGFAULT", 0);
	add_to_env("TMPDIR", ".TMPDIR", 0);
	add_to_env("USER", getlogin(), 0);
	add_to_env("LOGNAME", getlogin(), 0);
	if ((str = ft_getenv("SHLVL", g_env)))
	{
		i = ft_atoi(str);
		ft_strdel(&str);
		if ((str = ft_itoa(i + 1)))
		{
			add_to_env("SHLVL", str, 0);
			ft_strdel(&str);
		}
	}
	else
		add_to_env("SHLVL", "1", 0);
	return (0);
}

int					ft_init_set()
{
	char		buff[4096];
	char		*str;
	struct		utsname t_utsname;
	str = ft_itoa(getpid());
	add_to_env("PID", str, 1);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(getppid());
	add_to_env("PPID", str, 1);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(getuid());
	add_to_env("UID", str, 1);
	if (str)
		ft_strdel(&str);
	str = ft_itoa(geteuid());
	add_to_env("EUID", str, 1);
	if (str)
		ft_strdel(&str);
	add_to_env("IFS", " \t\n", 1);
	gethostname(buff, sizeof(buff));
	add_to_env("HOSTNAME", buff, 1);
	manage_info_history();
	struct stat statbuf;
	struct passwd *pwd;
	uname(&t_utsname);
	add_to_env("SYSNAME", t_utsname.sysname, 1);
	return (0);
}

char				*search_path_of_101sh(char *bin)
{
	char		*tmp;
	char		*tmp_1;
	char		*tmp_2;
	char		buff[4096];
	int			i[2];

	i[0] = 0;
	i[1] = 0;
	tmp = ft_strdup(getcwd(buff, sizeof(buff)));
	if (bin)
	{
		i[0] = ft_strlen(bin);
		while (i[0] >= 0)
		{
			if (bin[i[0]] == '/')
			{
				if (i[0] > 0 && bin[i[0] - 1] == '/')
				{
					while (i[0] > 0 && bin[i[0]] == '/')
						i[0] = i[0] - 1;
					i[0] = i[0] + 1;
				}
				if (!(i[0] == 0 || (i[0] == 1 && bin[0] == '.')))
				{
					if (bin[0] == '/' || bin[0] == '.')
					{
						while (bin[i[1]] == '.')
							i[1] = i[1] + 1;
						while (bin[i[1]] == '/')
							i[1] = i[1] + 1;
					}
					tmp_1 = ft_strsub(bin, i[1], i[0] - i[1]);
					tmp_2 = ft_strjoin("/", tmp_1);
					ft_strdel(&tmp_1);
					ft_strdel(&tmp_2);
					ft_strdel(&tmp);
					return (ft_strjoin(tmp, tmp_2));
				}
				i[0] = -1;
			}
			else
				i[0] = i[0] - 1;
		}
	}
	return (tmp);
}

int					ft_init_env(int ac, char **av)
{
	char			*tmp;
	extern char		**environ;

	tmp = NULL;
	g_env = ft_tabdup(environ);
//	ft_get_user_info();
	if ((tmp = search_path_of_101sh(av[0])))
	{
//		add_to_env("_", tmp, 0);
		ft_strdel(&tmp);
	}

	return (0);
}

int					ft_term_init(int ac, char **av)
{
	char			*term;

	if (ft_init_env(ac, av))
		return (1);
//	if (ft_init_set())
//		return (1);
	if (!(term = getenv("TERM")))
		term = "xterm-256color";
	if (tgetent(NULL, term) == ERR)
		return (1);
	return (0);
}
