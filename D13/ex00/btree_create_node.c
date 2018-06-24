#include "../btree.h"

t_btree *btree_create_node(int item)
{
	t_btree		*new;

	new = malloc(sizeof(t_btree));
	new->item = item;
	new->father = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
