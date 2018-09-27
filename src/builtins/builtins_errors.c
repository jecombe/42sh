/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_errors.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/19 08:12:50 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:53:37 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		ft_biflag(const char *cmd)
{
	ft_putchar_fd('-', 2);
	ft_putchar_fd(*cmd, 2);
	ft_putendl_fd(": invalid option.", 2);
}

static void		ft_binofound(const char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory.", 2);
}

int		ft_bierrors(const char *prgm, const char *cmd, t_bierror err)
{
	ft_putstr_fd("101sh: ", 2);
	ft_putstr_fd(prgm, 2);
	ft_putstr_fd(": ", 2);
	if (err == BIFLAG)
		ft_biflag(cmd);
	else if (err == BINOFOUND)
		ft_binofound(cmd);
	else if (err == BITOMANY)
		ft_putendl_fd("Too many arguments.", 2);
	else if (err == BITOFEW)
		ft_putendl_fd("Too few arguments.", 2);
	else if (err == BIEQUAL)
		ft_putendl_fd("Variable name contain '='.", 2);
	return (EXIT_FAILURE);
}
