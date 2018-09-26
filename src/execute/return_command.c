
#include "heart.h"

static int	ft_waiting()
{
	int status;
	int ret;

	status = 0;
	wait(&status);
	while(wait(NULL) > 0)
		;
	ret = WEXITSTATUS(status);
	if (ret > 0)
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int			ft_return_command(t_loop *loop)
{

	if (ft_waiting() == EXIT_SUCCESS)
	{
		if (loop->bin == NULL)
		{
			add_to_set("?", "1");
			return (EXIT_FAILURE);
		}
		add_to_set("?", "0");
		return (EXIT_SUCCESS);
	}
	add_to_set("?", "1");
	return (EXIT_FAILURE);
}
