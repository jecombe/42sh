

#include "../../include/heart.h"



void	envset_del(void)
{
	if (g_env)
		ft_tabdel(&g_env);
	if (g_set)
		ft_tabdel(&g_set);
}
