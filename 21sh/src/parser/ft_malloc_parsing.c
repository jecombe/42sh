#include "../../include/parsing.h"

t_redirect	*ft_malloc_redirect(void)
{
	t_redirect	*new;

	if (!(new = malloc(sizeof(t_redirect))))
		return (NULL);
	new->fd = NULL;
	new->redirect = TOKEN;
	new->file = NULL;
	new->next = NULL;
	new->prev = NULL;
	return(new);
}

t_op		*ft_malloc_op(void)
{
	t_op	*new;

	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->cmd = NULL;
	new->token = TOKEN;
	new->redirect = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_seq		*ft_malloc_seq(void)
{
	t_seq	*new;

	if (!(new = malloc(sizeof(t_seq))))
		return (NULL);
	new->token = TOKEN;
	new->op = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
