/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/21 06:07:06 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/init.h"
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

int					ft_get_user_info()
{
	struct stat statbuf;
	struct passwd *pwd;
	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		printf("%s\n", pwd->pw_name);
	else
		printf("%d\n", statbuf.st_uid);
	return (0);
}

int					manage_info_history(void)
{
	char		*str;
	char		*str2;
	char		buff[4096];
	int			fd;
	int			i;

	i = 0;
	ft_malloc_cmd(&g_set, "HISTSIZE=500");
	str2 = ft_strjoin(getcwd(buff, sizeof(buff)), "/.historic");
	if (!access(str2, F_OK))
	{
		str = ft_strjoin("HISTFILE=", str2);
		ft_malloc_cmd(&g_set, str);
		fd = open(str2, O_RDONLY);
		while (get_next_line(fd, &str2) > 0)
		{
			ft_strdel(&str2);
			i++;
		}
		close(fd);
		str2 = ft_itoa(i);
		str = ft_strjoin("HISTFILESIZE=", str2);
		ft_malloc_cmd(&g_set, str);
	}
	else
	{
		ft_malloc_cmd(&g_set, "HISTFILESIZE=NULL");
		ft_malloc_cmd(&g_set, "HISTFILE=UNKNOW");
	}
	return (0);
}

int					ft_init_set()
{
	char		buff[4096];
	char		*str;
	char		*str2;
	int			i = 0;
	struct utsname t_utsname;

	str = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
	ft_malloc_cmd(&g_set, str);
	str = ft_strjoin("101SH=", getcwd(buff, sizeof(buff)));
	ft_malloc_cmd(&g_set, str);
	ft_malloc_cmd(&g_set, "101SH_VERSION=21SH_PLEINS_DE_SEGFAULT");
	str2 = ft_itoa(getpid());
	str = ft_strjoin("PID=", str2);
	ft_malloc_cmd(&g_set, str);
	str2 = ft_itoa(getppid());
	str = ft_strjoin("PPID=", str2);
	ft_malloc_cmd(&g_set, str);
	str2 = ft_itoa(getuid());
	str = ft_strjoin("UID=", str2);
	ft_malloc_cmd(&g_set, str);
	str2 = ft_itoa(geteuid());
	str = ft_strjoin("EUID=", str2);
	ft_malloc_cmd(&g_set, str);
	ft_malloc_cmd(&g_set, "IFS='\\n\\t'");
	gethostname(buff, sizeof(buff));
	str = ft_strjoin("HOSTNAME=", buff);
	manage_info_history();
	ft_malloc_cmd(&g_set, str);
	str = ft_strjoin("USER=", getlogin());
	ft_malloc_cmd(&g_set, str);
	struct stat statbuf;
	struct passwd *pwd;
	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		printf("%s\n", pwd->pw_name);
	else
		printf("%d\n", statbuf.st_uid);
	uname(&t_utsname);
	printf("SYSNAME == %s\n", t_utsname.sysname);
	getdomainname(buff, sizeof(buff));
	printf("DOMAINE == %s\n", buff);
	ft_malloc_cmd(&g_set, buff);
//	ft_get_user_info();
//	str = ft_strjoin("LINE=", get_size_yterm);
//	ft_malloc_cmd(&g_set, get_size_Xterm());
//	str = ft_strjoin("COLUMNS=", get_size_xterm);
//	ft_malloc_cmd(&g_set, get_size_Yterm());
//	if (g_env)
//		if ((str = ft_getenv("", g_env)))
//			if (ft_malloc_cmd(&g_set, str))
//			return (1);
	while (g_set[i])
	{
		printf("G_SET[%d] = %s\n", i, g_set[i]);
		i++;
	}
	return (0);
}

char				*search_path_of_101sh(char *bin)
{
	char		*tmp;
	char		buff[4096];

	tmp = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
	printf("PWD == %s, BIN == %s\n", tmp, bin);
	return (tmp);
}

int					ft_init_env(int ac, char **av)
{
	char		*tmp;
	extern char		**environ;

	g_env = ft_tabdup(environ);
	printf("_=\"CHEMIN DU BINAIRE 101sh\"\n");
	tmp = search_path_of_101sh(av[0]);
	ft_get_user_info();
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
