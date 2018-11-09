/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:33:04 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 07:37:11 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int			ft_assign(t_op *exec)
{
	int			i;
	char		*name;
	char		*value;

	i = 1;
	while (exec->cmd[i])
	{
		name = ft_get_var(exec->cmd[i]);
		value = ft_get_value(exec->cmd[i]);
		add_to_set(name, value);
		if (name)
			ft_strdel(&name);
		if (value)
			ft_strdel(&value);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int			ft_search_assignement_word(int i, char **name)
{
	int j;
	int eq;

	while (name[i])
	{
		j = 0;
		if (ft_isalpha(name[i][0]))
		{
			eq = 0;
			while (name[i][j] && !eq)
			{
				if (name[i][j] == '=' || ft_isalnum(name[i][j]))
					eq = name[i][j++] == '=' ? 1 : 0;
				else
					return (i);
			}
			i += eq == 1 ? 1 : 0;
			if (!(eq == 1))
				return (i);
		}
		else
			return (i);
	}
	return (name[0] ? -1 : 0);
}

static int		ft_builtins_envset(t_op *opera)
{
	if ((FT_SETENV || FT_UNSETENV || FT_EXPORT || FT_UNSET) &&
			opera->cmd[1] && ft_strcmp(opera->cmd[1], "PATH") == 0)
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
	if (ft_search_assignement_word(0, opera->cmd))
		return (ft_assign(opera));
	return (EXIT_FAILURE);
}

int				ft_builtins(t_op *opera, t_loop *loop)
{
	t_hashtable *hashtable;

	hashtable = NULL;
	loop->exit = 0;
	ft_save_hash(&hashtable);
	if (FT_ENV || FT_SETENV || FT_UNSETENV || FT_SET || FT_EXPORT || FT_UNSET)
		return (ft_builtins_envset(opera));
	else if (FT_ASSIGN)
		return (ft_assign(opera));
	else if (FT_ECHO)
		return (ft_echo(opera));
	else if (FT_CD)
		return (ft_change_dir(opera->cmd));
	else if (FT_EXIT)
	{
		loop->exit = 1;
		return (ft_exit(opera));
	}
	else if (FT_HASH)
		ft_hash_print(hashtable);
	else if (FT_READ)
		ft_read(opera->cmd);
	return (EXIT_SUCCESS);
}
