#include "heart.h"

void		del_lines(int nb_line)
{
	int		i;

	i = nb_line;
	while (i > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("dl", NULL), 1, ft_putchar);
		i--;
	}
	tputs(tgetstr("up", NULL), 1, ft_putchar);
}

void		insert_lines(int nb_line)
{
	int		i;

	i = nb_line;
	while (i > 0)
	{
		tputs(tgetstr("al", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		i--;
	}
}
