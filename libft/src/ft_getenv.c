/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_getenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/24 20:46:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/23 05:11:55 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_getenv(char *str, char **env)
{
	int		i;
	int		j;

	i = -1;
	if (env)
		while (env[++i])
		{
			j = 0;
			while (env[i][j] == str[j] && env[i][j] && str[j])
				j++;
			if (env[i][j] == '=' && j != 0 && !str[j])
				return (ft_strdup((env[i]) + (j + 1)));
		}
	return (NULL);
}
