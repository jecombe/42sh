/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_export.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 06:59:18 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 10:25:21 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

int			to_add_at_env(char *cmd)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	name = NULL;
	value = NULL;
	if ((i = index_to_var(cmd, g_set)))
	{
		if ((name = ft_get_var(g_set[i])))
		{
			value = ft_get_value(g_set[i]);
			add_to_env(name, value);
			ft_strdel(&name);
			ft_strdel(&value);
		}
	}
	return (0);
}

void		export_error(char *str)
{
	ft_putstr("bash: export: `");
	ft_putstr(str);
	ft_putendl("': not a valid identifier");
}

int			str_isassign(char *str)
{
	int			i;

	i = 0;
	if (str)
		while (str[i])
		{
			if (ft_isalnum(str[i]) || (str[i] == '=' && i > 0))
				i++;
			else
				return (0);
		}
	return (1);
}

int			assign_var(char *cmd)
{
	char		*name;
	char		*value;

	name = ft_get_var(cmd);
	value = ft_get_value(cmd);
	add_to_set(name, value);
	add_to_env(name, value);
	return (0);
}

int			ft_export(t_op *exec)
{
	int		i;

	i = 1;
	while (exec->cmd[i])
	{
		if (ft_str_isalnum(exec->cmd[i]))
			to_add_at_env(exec->cmd[i]);
		else if (str_isassign(exec->cmd[i]))
			assign_var(exec->cmd[i]);
		else
			export_error(exec->cmd[i]);
		i++;
	}
	return (0);
}
