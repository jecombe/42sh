/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_assign.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 04:20:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 15:36:20 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/builtins.h"

int		ft_assign(t_op *exec)
{
	int			i;
	char		*name;
	char		*value;

	i = 1;
	while (exec->cmd[i])
	{
		printf("EXEC->cmd[%d] == %s\n", i, exec->cmd[i]);
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
