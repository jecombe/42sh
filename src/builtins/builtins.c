/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:33:04 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 03:51:58 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	ft_builtins_envset(t_op *opera)
{
	if ((FT_SETENV || FT_UNSETENV || FT_EXPORT || FT_UNSET) &&
			ft_strcmp(opera->cmd[0], "PATH") == 0)
		hash_clear();
	if (FT_ENV || (FT_SETENV && opera->cmd[1] == NULL))
		return (ft_env(opera));
	if (FT_SETENV)
	{
		if (opera->cmd[2] && opera->cmd[3])
			return (ft_bierrors("setenv", NULL, BITOMANY));
		return (ft_setenv(opera->cmd[1], opera->cmd[2]));
	}
	if (FT_UNSETENV)
		return (ft_unsetenv(opera->cmd[1]));
	if (FT_SET)
		return (set(opera));
	if (FT_UNSET)
		return (unset(opera));
	if (FT_EXPORT)
		return (ft_export(opera));
	return (EXIT_FAILURE);
}

int			ft_builtins(t_op *opera)
{
	t_hashtable *hashtable;

	hashtable = NULL;
	ft_save_hash(&hashtable);
	if (FT_ENV || FT_SETENV || FT_UNSETENV || FT_SET || FT_EXPORT || FT_UNSET)
		return (ft_builtins_envset(opera));
	else if (FT_ASSIGN)
		return (ft_assign(opera));
	else if (FT_ECHO)
		return (ft_echo(opera));
	else if (FT_CD)
		return (ft_cd(opera));
	else if (FT_EXIT)
		return (ft_exit(opera));
	else if (FT_HASH)
		ft_hash_print(hashtable);
	else if (FT_READ)
		ft_read(opera->cmd);
	return (EXIT_SUCCESS);
}
