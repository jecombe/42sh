

#include "heart.h"

int			prelexer(char *line)
{
	int		i;
	char	c;

	i = -1;
	c = 0;
	while (line[++i])
	{
		c = line[i];
		if (c == '"' || c == '\'')
			while (line[++i] != c)
				if (!line[i])
					return ((c == '"') ? B_QUOTE : S_QUOTE);
	}
	return (PROMPT);
}
