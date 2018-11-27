/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 19:49:39 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 14:19:09 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

char		ft_stat(char *file, char *path)
{
	char			ret;
	struct stat		stat;
	char			*tmp;
	char			*complete;

	tmp = path[1] ? ft_strjoin(path, "/") : ft_strdup(path);
	complete = ft_strjoin(tmp, file);
	free(tmp);
	ret = '0';
	if (lstat(complete, &stat) == -1 && (ft_strdel(&complete) + 1))
		return ('0');
	if ((stat.st_mode & S_IFMT) == S_IFDIR && (ft_strdel(&complete) + 1))
		return ('2');
	if ((stat.st_mode & S_IFMT) == S_IFLNK && (ft_strdel(&complete) + 1))
		return ('2');
	ft_strdel(&complete);
	ret = (stat.st_mode & S_IFMT) == S_IFREG ? '1' : '0';
	if (ret == '1')
	{
		ret = stat.st_mode & S_IXUSR ? '1' : '0';
		ret = stat.st_mode & S_IXGRP || ret == '1' ? '1' : '0';
		ret = stat.st_mode & S_IXOTH || ret == '1' ? '1' : '0';
	}
	return (ret);
}
