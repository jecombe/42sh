/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_file_directory.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 17:06:48 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 16:29:20 by jecombe     ###    #+. /#+    ###.fr     */
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

int				ft_check_source(char *source)
{
	struct stat sb;

	if (lstat(source, &sb) == -1)
		return (-3);
	return (0);
}

int				ft_check_permission(char *source)
{
	if (access(source, R_OK) == 0)
		return (0);
	return (-1);
}
