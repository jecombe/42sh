/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_echo.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:29:41 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/12 14:04:28 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int			ft_builtin_echo(char *arg[100])
{
	char	*tmp;

	tmp = NULL;
	arg++;
	while (*arg)
	{
		if (*arg[0] == '$')
			tmp = ft_getenv(ft_strrchr(*arg, '$') + 1);
		tmp == NULL ? ft_putstr(*arg) : ft_putstr(tmp);
		tmp != NULL ? ft_strdel(&tmp) : 0;
		ft_putchar(' ');
		arg++;
	}
	ft_putchar('\n');
	return (0);
}


int			ft_builtin_echo_output(char *arg[100], t_token *token, char *file, int flag)
{
	char	*tmp;
	//char *c;
	int fd;
	int i = 0;
	int ok = 0;
	int ok2 = 0;
	tmp = NULL;
	int flag2;
	(void)token;
	arg++;
	if (flag == O_RDONLY)
		flag2 = O_RDONLY;
	else
		flag2 = O_WRONLY;
	while (*arg)
	{
		i = 0;
		if (*arg[0] == '$')
		{
			ok++;
			tmp = ft_getenv(ft_strrchr(*arg, '$') + 1);
			if (ok2 == 0 && ok == 1 && flag2 == O_WRONLY)
				fd = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if (fd == -1)
				ft_putendl("Error");
			write(fd, tmp, ft_strlen(tmp));
			write(fd, " ", 1);
			if (flag2 == O_RDONLY)
			{
				fd = open(file, O_RDONLY);
				if (fd == -1)
				{
					ft_putendl("Erreur");
					return (0);
				}
			}
		}
		if (tmp == NULL)
		{
			if (ok == 0 && flag2 == O_WRONLY)
			{
				ok2++;
				fd = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			}
			if (fd == -1)
				ft_putendl("Error");
			i = 0;
			while (*arg)
			{
				if (*arg[0] == '$')
				{
					tmp = ft_getenv(ft_strrchr(*arg, '$') + 1);
					write(fd, tmp, ft_strlen(tmp));
					write(fd, " ", 1);
					arg++;
				}
				else
				{
					write(fd, *arg, ft_strlen(*arg));
					write(fd, " ", 1);
					arg++;
				}
			}
			if (flag2 == O_RDONLY)
			{
				fd = open(file, O_RDONLY);
				if (fd == -1)
				{
					printf("Erreur");
					return (0);
				}
			}
		}
		tmp != NULL ? ft_strdel(&tmp) : 0;
		arg++;
	}
	write(fd, "\n", 1);
	close(fd);
	return (0);
}
