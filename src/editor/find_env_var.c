/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_path.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 01:33:09 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:09:29 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

char	*var_directory(char *var_value, char *var_dir)
{
	char path_dir[4096];

	ft_strcpy(path_dir, var_value);
	ft_strcat(path_dir, var_dir);
	return (ft_strdup(path_dir));
}

char	*find_env_var(char **env, char *var, int mode)
{
	int		i;
	int		j;
	int		size;
	char	tmp_var[4096];

	i = -1;
	j = -1;
	if (!var)
		return (NULL);
	while (env[++i])
	{
		size = -1;
		while (env[i][++size] != '=')
			tmp_var[size] = env[i][size];
		tmp_var[size] = '\0';
		if (!mode ? !ft_strcmp(tmp_var, var) : !ft_strncmp(tmp_var, var, size))
			while (env[i][++j])
			{
				if (env[i][j] == '=' && (var[size] != '/' || var[size] != ' '))
					return (ft_strdup(env[i] + j + 1));
				if (env[i][j] == '=' && (var[size] == '/' || var[size] == ' '))
					return (var_directory(env[i] + j + 1, var + size));
			}
	}
	return (NULL);
}
