/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_echo.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:29:41 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 15:57:00 by jecombe     ###    #+. /#+    ###.fr     */
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

char		*ft_give_me_name(t_token *token, int co)
{
	int i;
	t_token *tmptock;

	i = 1;
	tmptock = token;
	char *c;
	while (i != co + 2)
	{
		if (i == 3)
		{
			c = tmptock->id;
			return (c);
		}
		tmptock = tmptock->next;
		i++;
	}
	return (NULL);
}


int			ft_builtin_echo_output(char *arg[100], t_token *token, int co)
{
	char	*tmp;
	char *c;
	int fd;
	int i = 0;
	int ok = 0;
	int ok2 = 0;
	tmp = NULL;
	c = ft_give_me_name(token, co);
	arg++;
	while (*arg)
	{
		i = 0;
		if (*arg[0] == '$')
		{
			ok++;
			tmp = ft_getenv(ft_strrchr(*arg, '$') + 1);
			if (ok2 == 0 && ok == 1)
				{
					fd = open(c, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				}
			if (fd == -1)
				ft_putendl("Error");
				write(fd, tmp, ft_strlen(tmp));
			write(fd, " ", 1);
		}
		if (tmp == NULL)
		{
			if (ok == 0)
			{
				ok2++;
				fd = open(c, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
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
		}
	tmp != NULL ? ft_strdel(&tmp) : 0;
		arg++;
	}
	write(fd, "\n", 1);
	close(fd);
	return (0);
}
