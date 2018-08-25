/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backslash_manager.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 20:13:12 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 20:13:14 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

int			backslash_out_dquote(char **cmd, int *j)
{
	char		*tmp;
	int			i;
	int			i2;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(*cmd));
	while (i < *j)
	{
		tmp[i] = (*cmd)[i];
		i++;
	}
	i2 = i;
	i++;
	while ((*cmd)[i])
	{
		tmp[i2] = (*cmd)[i];
		i++;
		i2++;
	}
	tmp[i2] = '\0';
	ft_strdel(&(*cmd));
	*cmd = ft_strdup(tmp);
	return (0);
}

int			backslash_manager(char ***cmd, int i, int *j, int d_quote)
{
	if (d_quote == 0)
		backslash_out_dquote(&(*cmd)[i], j);
	else
		*j = *j + 1;
	*j = *j + 1;
	return (0);
}
