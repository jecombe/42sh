/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:25:35 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 17:15:08 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

char	*ft_go_to(char *bin, int nb)
{
	int i;

	i = 0;
	while (nb)
	{
		bin++;
		nb--;
	}
	return (bin);
}

int			ft_check_direct_command(char *cmd)
{
	struct stat sb;
	if (lstat(cmd, &sb) == -1)
		return (-1);
	else
		return (0);
}

int				ft_check_file_is_directory(char *file)
{
	struct stat st;
	stat(file, &st);
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr("is a directory: ");
		ft_putendl(file);
		return (-1);
	}
	else
		return (0);
}

int		ft_check_source(char *source)
{
	struct stat sb;

printf("OKOKOKOKO\n");
	if (lstat(source, &sb) == -1)
	{
		ft_putstr("no such file or directory: ");
		ft_putendl(source);

		return (-1);
	}
	return (0);
}


