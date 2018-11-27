/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 05:59:21 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 08:07:52 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void			ft_patch_curpath_slashs_and_dots(char **path)
{
	int				i;
	int				slash;

	slash = 0;
	i = -1;
	while ((*path)[++i])
		if ((*path)[i] == '.' && i && (*path)[i - 1] == '/' &&
				(!(*path)[i + 1] || (*path)[i + 1] == '/'))
			ft_chardel_at(path, i--);
	i = -1;
	while ((*path)[++i])
		while (!ft_strncmp((*path) + i, "//", 2))
			ft_chardel_at(path, i);
	i = -1;
	while ((i < 0 ? i = slash : 0) >= 0 && (*path)[++i])
		if ((*path)[i] == '/' && (ft_strncmp((*path) + i + 1, "..", 2)
					&& ft_strlen((*path) + i) > 1
					&& !(!(*path)[i + 2] || (*path)[i + 2] == '/')))
			slash = i;
		else if (!ft_strncmp((*path) + i, "..", 2) && (!(*path)[i + 2] ||
					((i && (*path)[i - 1] == '/') && (*path)[i + 2] == '/')))
			while (i-- >= slash || !ft_strncmp((*path) + slash, "//", 2))
				ft_chardel_at(path, slash + 1);
	if (ft_strlen(*path) > 1 && (*path)[ft_strlen(*path) - 1] == '/')
		(*path)[ft_strlen(*path) - 1] = '\0';
}

static int			ft_chdir_and_env(char *curpath, char option)
{
	char	cwd[2048];
	char	*pwd;

	ft_patch_curpath_slashs_and_dots(&curpath);
	if ((pwd = ft_getenv("PWD", g_env)))
	{
		ft_setenv("OLDPWD", pwd);
		free(pwd);
	}
	else
		ft_setenv("OLDPWD", getcwd(cwd, sizeof(cwd)));
	chdir(curpath);
	if (option == 'P')
		ft_setenv("PWD", getcwd(cwd, sizeof(cwd)));
	else
		ft_setenv("PWD", curpath);
	ft_strdel(&curpath);
	return (EXIT_SUCCESS);
}

static char			*ft_check_curpath(char *curpath, char **cmd)
{
	struct stat		path_stat;

	stat(curpath, &path_stat);
	if (!access(curpath, F_OK) && S_ISDIR(path_stat.st_mode))
	{
		if (access(curpath, R_OK))
			ft_print_error("cd", "permission denied.");
		else
			return (curpath);
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		if (*cmd && ft_strcmp(*cmd, "-"))
			ft_putendl_fd(*cmd ? *cmd : "", 2);
		else
			ft_putendl_fd(curpath ? curpath : "", 2);
	}
	ft_strdel(&curpath);
	return (NULL);
}

static char			*ft_get_curpath(char **cmd, char option)
{
	char			cwd[2048];
	char			*curpath;
	char			*tmp;

	if (cmd[0] && !ft_strcmp(cmd[0], "-"))
		curpath = ft_getenv("OLDPWD", g_env);
	else if (cmd[0] && cmd[0][0] == '/')
		curpath = ft_strdup(cmd[0]);
	else if (cmd[0] && (curpath = ft_memalloc(ft_strlen(cmd[0]) + sizeof(cwd))))
	{
		if (option == 'P')
			ft_geoprintf(curpath, "%s/%s", getcwd(cwd, sizeof(cwd)), cmd[0]);
		else
		{
			tmp = ft_getenv("PWD", g_env);
			ft_geoprintf(curpath, "%s/%s", tmp, cmd[0]);
			ft_strdel(&tmp);
		}
	}
	else
		curpath = ft_getenv("HOME", g_env);
	return (ft_check_curpath(curpath, cmd));
}

int					ft_change_dir(char **cmd)
{
	int				i;
	int				j;
	char			option;
	char			*curpath;

	option = '\0';
	i = 0;
	while (!(j = 0) && cmd[++i] && cmd[i][j] == '-' && ft_strcmp(cmd[i], "-"))
		while (cmd[i][++j])
			if (cmd[i][j] == 'P')
				option = 'P';
			else if (cmd[i][j] != 'L')
			{
				ft_putstr_fd("cd: bad option: ", 2);
				ft_putendl_fd(cmd[i] + j, 2);
				return (EXIT_FAILURE);
			}
	if ((curpath = ft_get_curpath(cmd + i, option)))
		return (ft_chdir_and_env(curpath, option));
	return (EXIT_FAILURE);
}
