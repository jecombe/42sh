/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_exit.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/23 09:42:35 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 15:24:06 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_builtin_exit_error(char *arg[100])
{
	int		i;

	i = -1;
	if (arg[1] != NULL)
	{
		while (arg[1][++i])
			if (!ft_isdigit(arg[1][i]))
				return (ft_error_exit(arg[1], 1));
		if (arg[2] != NULL)
		{
			ft_error_exit("", 2);
			return (2);
		}
		if (ft_atoi(arg[1]) > 0)
			return (1);
	}
	return (0);
}

int			ft_builtin_exit(t_token *token, char *arg[100])
{
	int		stat;
	int		i;

	ft_putendl("exit");
	stat = ft_builtin_exit_error(arg);
	if (stat == 0 || stat == 1)
	{
		ft_token_del(token);
		ft_env_del();
		i = -1;
		while (arg[++i] && (i < 100))
			ft_strdel(&arg[i]);
		if (stat == 0)
			exit(EXIT_SUCCESS);
		else if (stat == 1)
			exit(EXIT_FAILURE);
	}
	return (1);
}
