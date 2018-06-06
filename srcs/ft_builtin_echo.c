/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_echo.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:29:41 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 02:52:52 by dzonda      ###    #+. /#+    ###.fr     */
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
