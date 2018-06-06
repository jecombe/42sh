/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/13 02:15:27 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 02:42:25 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_cd(const char *name, int stat)
{
	if (stat == 1)
		ft_putendl_fd("cd: too many arguments", 2);
	if (stat == 2)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(RED, 2);
		ft_putendl_fd(name, 2);
		ft_putstr_fd(END, 2);
	}
	return (1);
}

int		ft_error_env(const char *name, int stat)
{
	if (stat == 1)
		ft_putendl_fd("setenv: too few arguments", 2);
	if (stat == 2)
	{
		ft_putstr_fd("setenv: NAME contains '=': ", 2);
		ft_putstr_fd(RED, 2);
		ft_putendl_fd(name, 2);
	}
	if (stat == 3)
		ft_putendl_fd("setenv: too many arguments", 2);
	if (stat == 4)
		ft_putendl_fd("unsetenv: too few arguments", 2);
	if (stat == 5)
	{
		ft_putstr_fd("unsetenv: not found in environment: ", 2);
		ft_putstr_fd(RED, 2);
		ft_putendl_fd(name, 2);
	}
	if (stat == 6)
		ft_putendl_fd("unsetenv: too many arguments", 2);
	ft_putstr_fd(END, 2);
	(stat == 1 || stat == 2 || stat == 3 || stat == 4) ?
		ft_putendl_fd("usage: setenv [NAME] [VALUE]", 2) :
		ft_putendl_fd("usage: unsetenv [NAME]", 2);
	return (1);
}

int		ft_error_exit(const char *name, int stat)
{
	if (stat == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(END, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	if (stat == 2)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (1);
}

int		ft_error_none(const char *name)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(RED, 2);
	ft_putendl_fd(name, 2);
	ft_putstr_fd(END, 2);
	return (1);
}
