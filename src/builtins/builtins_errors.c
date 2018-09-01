/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_errors.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/19 08:12:50 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 16:46:56 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void		ft_biflag(const char *prgm, const char *cmd)
{
	ft_putchar_fd('-', STDERR_FILENO);
	ft_putchar_fd(*cmd, STDERR_FILENO);
	ft_putendl_fd(": invalid option.", STDERR_FILENO);
}

static void		ft_binofound(const char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory.", STDERR_FILENO);
}

int		ft_bierrors(const char *prgm, const char *cmd, t_bierror err)
{
	ft_putstr_fd("101sh: ", STDERR_FILENO);
	ft_putstr_fd(prgm, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err == BIFLAG)
		ft_biflag(prgm, cmd);
	else if (err == BINOFOUND)
		ft_binofound(cmd);
	else if (err == BITOMANY)
		ft_putendl_fd("Too many arguments.", STDERR_FILENO);
	else if (err == BITOFEW)
		ft_putendl_fd("Too few arguments.", STDERR_FILENO);
	else if (err == BIEQUAL)
		ft_putendl_fd("Variable name contain '='.", STDERR_FILENO);
	return (EXIT_FAILURE);
}
