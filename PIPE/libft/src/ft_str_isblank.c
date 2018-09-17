#include "../include/libft.h"
#include <stdio.h>

int		ft_str_isblank(char *str)
{
	int		i;

	i = 0;
	if (str && str[i])
	{
		while (str[i])
		{
			if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
				return (0);
			i++;
		}
	}
	return (1);
}
