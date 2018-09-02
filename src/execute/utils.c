/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:25:35 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 09:03:01 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void	ft_print_error(const char *s1, const char *s2)
{
	ft_putstr_color("42sh: ", 14);
	ft_putstr_color(s1, 9);
	ft_putstr(STOP);
	ft_putstr_color(": ", 9);
	ft_putstr_color(s2, 9);
	ft_putstr(STOP);
	ft_putchar('\n');
}

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
	if (access(file, F_OK) == 0)
	{
		printf("NOOOOOOOOOOOOOOOOOO %s\n", file);
		return (-1);
	}
	else
		printf("GOODn");
		return (0);
/*	struct stat st;
	stat(file, &st);
	if (S_ISDIR(st.st_mode))
	{
		//ft_print_error(file, "is a directory");
		return (-1);
	}
	else
		return (0);*/
}

int		ft_check_source(char *source)
{
	if (access(source, F_OK) == 0)
	{
		printf("GOOOd\n");
		return (0);
	}
	else
		printf("NOOo\n");
		return (-1);
}

/*int				ft_check_file_is_directory(char *file)
{
	struct stat st;
	stat(file, &st);
	if (S_ISDIR(st.st_mode))
	{
		ft_print_error(file, "is a directory");
		return (-1);
	}
	else
		return (0);
}

int		ft_check_source(char *source)
{
	struct stat sb;

	if (lstat(source, &sb) == -1)
	{
		ft_print_error(source, "no such file or directory");
		return (-1);
	}
	return (0);
}*/
