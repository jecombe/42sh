/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_file_directory.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 17:06:48 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 17:11:06 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				ft_check_file_is_directory(const char *file)
{
	struct stat st;

	if (stat(file, &st) == 0 && S_ISDIR(st.st_mode))
		return (-1);
	return (0);
}

int				ft_check_file_is_regular(const char *file)
{
	struct stat st;

	if (stat(file, &st) == 0 && S_ISREG(st.st_mode))
		return (-4);
	return (0);
}

int				ft_check_file_is_regular2(const char *file)
{
	struct stat st;

	if (stat(file, &st) == 0 && st.st_mode & S_IXUSR)
		return (-5);
	return (0);
}

int				ft_check_source(char *source)
{
	struct stat sb;

	if (lstat(source, &sb) == -1)
		return (-3);
	return (0);
}

int				ft_check_direct_command(char *cmd)
{
	struct stat sb;

	if (lstat(cmd, &sb) == -1)
		return (-1);
	return (0);
}
