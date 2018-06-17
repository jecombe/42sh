#include "includes/minishell.h"

char		*ft_search_occurences(char *occurence, char *file, int version)
{
	int				i;

	i = 0;
	if (file != NULL && occurence != NULL)
	{
		while (occurence[i] && file[i])
		{
			if (occurence[i] != file[i])
				return (NULL);
			i++;
		}
		if (version == 0)
		{
			if (!occurence[i] && file[i])
				return (file);
		}
		else if (version == 1)
			if (!occurence[i])
				return (file);
	}
	return (NULL);
}
