/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 19:49:39 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 12:18:17 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

//REVOIR CETTE FONCTION CA FONCTIONNE QUE QUAND C EST DANS LE DOSSIER COURANT !!!

char		ft_is_exec(char *pwd, char *file)
{
	char			ret;
	struct stat		stat;

	printf("PWD == %s\n", pwd);
	sleep(2);
	ret = '0';
	if (lstat(pwd, &stat) == -1)
		return (0);
	if ((stat.st_mode & S_IFMT) == S_IFDIR)
		return ('2');
	ret = (stat.st_mode & S_IFMT) == S_IFREG ? '1' : '0';
	if (ret == 1)
	{
		ret = stat.st_mode & S_IXUSR ? '1' : '0';
		ret = stat.st_mode & S_IXGRP || ret == '1' ? '1' : '0';
		ret = stat.st_mode & S_IXOTH || ret == '1' ? '1' : '0';
	}
	return (ret);
}

char		ft_is_file(char *file, char *path)
{
	struct dirent	*dirent;
	char			ret;

	ret = ft_is_exec(file, path);
	return ('0');
}
