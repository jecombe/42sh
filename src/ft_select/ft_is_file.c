/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 19:49:39 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 10:57:09 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

//REVOIR CETTE FONCTION CA FONCTIONNE QUE QUAND C EST DANS LE DOSSIER COURANT !!!

static char	*ft_complete_path(char *src, char *file)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(src, "/");
	tmp2 = ft_strjoin(tmp, file);
	if (tmp)
		ft_strdel(&tmp);
	return (tmp2);
}

static int	ft_is_dir(char *pwd, char *file, DIR *dir)
{
	char	*test_is_dir;

	test_is_dir = ft_complete_path(pwd, file);
	if ((dir = opendir(test_is_dir)))
	{
		closedir(dir);
		if (test_is_dir)
			ft_strdel(&test_is_dir);
		return (1);
	}
	if (test_is_dir)
		ft_strdel(&test_is_dir);
	return (0);
}

int			ft_is_exec(char *pwd, char *file)
{
	char			*tmp;
	int				ret;
	struct stat		stat;

	tmp = ft_complete_path(pwd, file);
	printf("PWD == %s\n", tmp);
	sleep(2);
	ret = lstat(tmp, &stat);
	if (ret == -1)
		return (0);
	ret = (stat.st_mode & S_IFMT) == S_IFREG ? 1 : 0;
	if (ret == 1)
	{
		ret = stat.st_mode & S_IXUSR ? 1 : 0;
		ret = stat.st_mode & S_IXGRP || ret == 1 ? 1 : 0;
		ret = stat.st_mode & S_IXOTH || ret == 1 ? 1 : 0;
	}
	if (tmp)
		ft_strdel(&tmp);
	return (ret);
}

int			ft_is_file(char *file, int index)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;

	pwd = getenv("PWD");
	ret = 0;
	dir = NULL;
	if ((dir = opendir(pwd)))
	{
		while ((dirent = readdir(dir)) != NULL)
			if (!ft_strcmp(dirent->d_name, file))
			{
				ret = ft_is_exec(pwd, file);
				closedir(dir);
				return (ret == 0 ? 3 : 2);
			}
		closedir(dir);
	}
	return (0);
}
