/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_set.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:58:09 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 09:03:58 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int			add_info_params(const char **av)
{
	char	*tmp;
	int		i;
	char	*etoile;

	tmp = NULL;
	i = -1;
	etoile = NULL;
	while (av[++i])
	{
		tmp = ft_itoa(i);
		add_to_set(tmp, (char *)av[i]);
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
	}
	add_to_set("*", etoile);
	ft_strdel(&etoile);
	return (EXIT_SUCCESS);
}

static void			add_info_id(void)
{
	char	*str;
	char	buff[BUFF_SIZE];

	str = NULL;
	ft_bzero(buff, BUFF_SIZE);
	if ((str = ft_itoa(getppid())))
		add_to_set("PPID", str);
	ft_strdel(&str);
	if ((str = ft_itoa(getuid())))
		add_to_set("UID", str);
	ft_strdel(&str);
	if ((str = ft_itoa(geteuid())))
		add_to_set("EUID", str);
	ft_strdel(&str);
	if ((gethostname(buff, sizeof(buff))) == 0)
		add_to_set("HOSTNAME", buff);
}

static int			get_sysname(void)
{
	char			*tmp;
	struct utsname	t_utsname;
	struct stat		statbuf;

	tmp = NULL;
	ft_memset(&t_utsname, 0, sizeof(struct utsname));
	ft_memset(&statbuf, 0, sizeof(struct stat));
	if ((uname(&t_utsname)) == 0)
		add_to_set("SYSNAME", t_utsname.sysname);
	add_to_set("?", "0");
	if ((tmp = ft_itoa(getpid())))
	{
		add_to_set("PID", tmp);
		add_to_set("$", tmp);
	}
	ft_strdel(&tmp);
	return (0);
}

int					init_set(int ac, const char **av)
{
	(void)ac;
	if (g_env)
		g_set = ft_tabdup(g_env);
	add_info_params(av);
	add_info_id();
	add_to_set("IFS", " \t\n");
	get_sysname();
	return (EXIT_SUCCESS);
}
