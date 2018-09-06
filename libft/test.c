
#include "./include/libft.h"

int main(int argc, const char *argv[])
{
	char **s;
	extern char **environ;

	s = NULL;
	s = ft_tabdup(environ);
	ft_tabdel(&s);
	return 0;
}
