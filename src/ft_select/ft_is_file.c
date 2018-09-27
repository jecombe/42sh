/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 19:49:39 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 14:31:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

//REVOIR CETTE FONCTION CA FONCTIONNE QUE QUAND C EST DANS LE DOSSIER COURANT !!!

char		ft_stat(char *file, char *path)
{
	char			ret;
	struct stat		stat;
	char			*tmp;
	char			*complete;

	tmp = path[1] ? ft_strjoin(path, "/") : ft_strdup(path);
	complete = ft_strjoin(tmp, file);
//	printf("COMPLETE == %s\n", complete);
	ret = '0';
	if (lstat(complete, &stat) == -1)
		return ('0');
	if ((stat.st_mode & S_IFMT) == S_IFDIR)
	{
//		printf("STAT == 2\n");
		return ('2');
	}
	ret = (stat.st_mode & S_IFMT) == S_IFREG ? '1' : '0';
	if (ret == '1')
	{
		ret = stat.st_mode & S_IXUSR ? '1' : '0';
		ret = stat.st_mode & S_IXGRP || ret == '1' ? '1' : '0';
		ret = stat.st_mode & S_IXOTH || ret == '1' ? '1' : '0';
	}
//	printf("STAT == %c\n", ret);
	return (ret);
}
