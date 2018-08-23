/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/23 06:18:58 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

char				*concat_name_value(char *name, char *value)
{
	char		*str;
	char		*str2;

	str = NULL;
	str2 = NULL;
	if (!name || !value)
		return (NULL);
	str2 = ft_strjoin(name, "=");
	str = ft_strjoin(str2, value);
	return (str);
}

int					add_to_env(char *name, char *value, char ***env)
{
	int			i;
	int			j;
	int			find;
	char		*to_add;
	char		*tmp;

	find = 0;
	i = 0;
	to_add = concat_name_value(name, value);
	if (*env)
		while ((*env)[i] && find == 0)
		{
			j = 0;
			while ((*env)[i][j] == name[j] && (*env)[i][j] && name[j])
				j++;
			if ((*env)[i][j] == '=' && j != 0)
				find = 1;
			else
				i++;
		}
	if (find == 1)
	{
		ft_strdel(&(*env)[i]);
		(*env)[i] = ft_strdup(to_add);
	}
	else
	{
		if (*env && (*env)[0])
		{
			j = ft_tablen(*env) - 1;
			if (!ft_strncmp((*env)[j], "_=", 2))
			{
				tmp = ft_strdup((*env)[j]);
				ft_strdel(&(*env)[j]);
				(*env)[i] = ft_strdup(to_add);
				ft_malloc_cmd(env, tmp);
			}
			else
			{
				ft_malloc_cmd(env, to_add);
			}
		}
		else
			ft_malloc_cmd(&(*env), to_add);
	}
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
		add_to_env("HISTFILE", str, &g_env);
		fd = open(str, O_RDONLY);
		while (get_next_line(fd, &str) > 0)
		{
			ft_strdel(&str);
			i++;
		}
		close(fd);
		str = ft_itoa(i);
		add_to_env("HISTFILESIZE", str, &g_env);
	}
	else
	{
		add_to_env("HISTFILESIZE", "NULL", &g_env);
		add_to_env("HISTFILE", "UNKNOW", &g_env);
	}
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


int					ft_get_user_info()
{
	char		buff[4096];
	char		*str;
	int			i = 0;

	add_to_env("PWD", getcwd(buff, sizeof(buff)), &g_env);
	add_to_env("SHELL", "/bin/bash", &g_env);
	if ((str = ft_strjoin("/Users/", getlogin())))
		add_to_env("HOME", str, &g_env);
	if (str)
		ft_strdel(&str);
	add_to_env("101SH_VERSION", "21SH_PLEINS_DE_SEGFAULT", &g_env);
	add_to_env("USER", getlogin(), &g_env);
	add_to_env("LOGNAME", getlogin(), &g_env);
	if ((str = ft_getenv("SHLVL", g_env)))
	{
		i = ft_atoi(str);
		ft_strdel(&str);
		if ((str = ft_itoa(i + 1)))
		{
			add_to_env("SHLVL", str, &g_env);
			ft_strdel(&str);
		}
	}
	else
		add_to_env("SHLVL", "1", &g_env);
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
		add_to_env("TMPDIR", tmp2, &g_env);
		ft_strdel(&tmp2);
		tmp2 = ft_strjoin(tmp, "/101sh");
		add_to_env("_", tmp2, &g_env);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (0);
}

int					ft_init_set()
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
	manage_info_history();
	struct stat statbuf;
	struct passwd *pwd;
	uname(&t_utsname);
	add_to_env("SYSNAME", t_utsname.sysname, &g_set);
	return (0);
}

int					ft_term_init(int ac, char **av)
{
	char			*term;

	if (ft_init_env(ac, av))
		return (1);
	if (ft_init_set())
		return (1);
	if (!(term = getenv("TERM")))
		term = "xterm-256color";
	if (tgetent(NULL, term) == ERR)
		return (1);
	return (0);
}
