/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 09:41:37 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/init.h"
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

void				historic_found(char *str)
{
	int			fd;
	int			i;
	char		*line;

	i = 0;
	line = NULL;
	add_to_set("HISTFILE", str);
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_strdel(&line);
		i++;
	}
	close(fd);
	line = ft_itoa(i);
	add_to_set("HISTFILESIZE", line);
	ft_strdel(&line);
}

int					manage_info_history(char *av)
{
	char		*str;
	char		buff[4096];

	add_to_set("HISTSIZE", "500");
	str = ft_strjoin(search_path_of_101sh(av), "/.101sh_history");
	if (access(str, F_OK) == 0)
	{
		historic_found(str);
	}
	else
	{
		add_to_set("HISTFILESIZE", "NULL");
		add_to_set("HISTFILE", "UNKNOW");
	}
	if (str)
		ft_strdel(&str);
	return (0);
}

int					get_sysname(int ac)
{
	char			*tmp;
	struct			utsname t_utsname;
	struct stat		statbuf;
	struct passwd	*pwd;

	uname(&t_utsname);
	add_to_set("SYSNAME", t_utsname.sysname);
	if ((tmp = ft_itoa(ac)))
	{
		add_to_set("#", tmp);
		ft_strdel(&tmp);
	}
	tmp = ft_itoa(getpid());
	add_to_set("PID", tmp);
	add_to_set("$", tmp);
	if (tmp)
		ft_strdel(&tmp);
	return (0);
}

int					add_info_params(int ac, char **av)
{
	char		*tmp;
	int			i;
	char		*etoile;

	i = 0;
	etoile = NULL;
	while (av[i])
	{
		tmp = ft_itoa(i);
		add_to_set(tmp, av[i]);
		ft_strdel(&tmp);
		if (etoile)
		{
			tmp = ft_strjoin(etoile, "\n");
			ft_strdel(&etoile);
			etoile = ft_strjoin(tmp, av[i]);
			ft_strdel(&tmp);
		}
		else
			etoile = ft_strdup(av[i]);
		i++;
	}
	add_to_set("*", etoile);
	etoile ? ft_strdel(&etoile) : 0;
	return (0);
}

int					init_set(int ac, char **av)
{
	char		buff[4096];
	char		*str;

	g_set = ft_tabdup(g_env);
	add_info_params(ac, av);
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
	manage_info_history(av[0]);
	get_sysname(ac);
	return (0);
}
