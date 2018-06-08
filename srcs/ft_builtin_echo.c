/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_echo.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:29:41 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 13:12:17 by jecombe     ###    #+. /#+    ###.fr     */
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
	tmp = NULL;
	c = ft_give_me_name(token, co);
	printf("--> %s\n", c);
	printf("--> %s\n", arg[0]);
	printf("--> %s-\n-", arg[1]);
	printf("--> %s\n", token->id);
	arg++;
	while (*arg)
	{
		if (*arg[0] == '$')
			tmp = ft_getenv(ft_strrchr(*arg, '$') + 1);
		if (tmp == NULL)
		{
			printf("OK\n");
			fd = open(c, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if (fd == -1)
				ft_putendl("Error");
			while (*arg)
			{
				write(fd, *arg, ft_strlen(*arg));
				write(fd, " ", 1);
				arg++;

			}
			close(fd);
			return (0);
		}
		//tmp == NULL ? ft_putstr(*arg) : ft_putstr(tmp);
		tmp != NULL ? ft_strdel(&tmp) : 0;
		ft_putchar(' ');
		arg++;
	}
	ft_putchar('\n');
	return (0);
}
