/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_getenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/24 20:46:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/05 02:47:48 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../../include/stdin.h"

char		*ft_getenv(char *str)
{
	int		i;
	int		j;

	i = -1;
	while (g_env[++i])
	{
		j = 0;
		while (g_env[i][j] == str[j] && g_env[i][j] && str[j])
			j++;
		if (g_env[i][j] == '=' && j != 0)
			return (ft_strdup((g_env[i]) + (j + 1)));
	}
	return (NULL);
}
