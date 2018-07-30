/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_io_search_dyn.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/03 07:01:52 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/03 07:36:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_error_search_dyn()
{
	ft_putendl("search_dyn: Just one option in argument");
	ft_putendl("-e for enable, -d for disable");
	return (-2);
}

int		ft_io_search_dyn(char **command, char ***my_env)
{
	char	**tablo;

	if (command[1] && !command[2])
	{
		if (ft_strcmp(command[1], "-e") == 0 && !command[2])
		{
			tablo = malloc(sizeof(char*) * 2 + 1);
			tablo[2] = NULL;
			tablo[0] = ft_strdup(command[0]);
			tablo[1] = ft_strdup("ON");
			ft_setenv(&(*my_env), tablo);
			printf("\n\r-e activer\n\r");
		}
		else if (ft_strcmp(command[1], "-d") == 0 && !command[2])
		{
			free(&command[1]);
			command[1] = ft_strdup("OFF");
			ft_setenv(&(*my_env), command);
			printf("\n\r-d activer\r\n");
		}
		else
			ft_error_search_dyn();
	}
	else
		ft_error_search_dyn();
	return (1);
}
