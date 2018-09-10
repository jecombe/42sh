/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_errors.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/19 08:12:50 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:39:05 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		ft_biflag(const char *prgm, const char *cmd, int fd_open)
{
	ft_putchar_fd('-', fd_open);
	ft_putchar_fd(*cmd, fd_open);
	ft_putendl_fd(": invalid option.", fd_open);
}

static void		ft_binofound(const char *cmd, int fd_open)
{
	ft_putstr_fd(cmd, fd_open);
	ft_putendl_fd(": No such file or directory.", fd_open);
}

int		ft_bierrors(const char *prgm, const char *cmd, t_bierror err, int fd_open)
{
	ft_putstr_fd("101sh: ", fd_open);
	ft_putstr_fd(prgm, fd_open);
	ft_putstr_fd(": ", fd_open);
	if (err == BIFLAG)
		ft_biflag(prgm, cmd, fd_open);
	else if (err == BINOFOUND)
		ft_binofound(cmd, fd_open);
	else if (err == BITOMANY)
		ft_putendl_fd("Too many arguments.", fd_open);
	else if (err == BITOFEW)
		ft_putendl_fd("Too few arguments.", fd_open);
	else if (err == BIEQUAL)
		ft_putendl_fd("Variable name contain '='.", fd_open);
	return (EXIT_FAILURE);
}
