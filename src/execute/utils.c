/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:25:35 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 13:33:13 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	ft_print_error(const char *s1, const char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

int				ft_check_file_is_directory(char *file)
{
	struct stat st;

	stat(file, &st);
	if (S_ISDIR(st.st_mode))
		return (-1);
	return (0);
}

int		ft_check_source(char *source)
{
	struct stat sb;

	if (lstat(source, &sb) == -1)
		return (-3);
	return (0);
}

void		ft_print_message(char *source, int nb)
{
	if (nb == -1)
		ft_print_error(source, "is a directory");
	else if (nb == -2)
		ft_print_error(source, "permission denied !");
	else if (nb == -3)
		ft_print_error(source, "no such file or directory");
}

int			ft_check_direct_command(char *cmd)
{
	struct stat sb;

	if (lstat(cmd, &sb) == -1)
		return (-1);
	return (0);
}
