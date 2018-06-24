#include "../btree.h"

void btree_insert_data(t_btree **root, int item, int (*cmpf)(int, int))
{
	t_btree		*now;

	if (!(*root))
		*root = btree_create_node(item);
	else
	{
		now = *root;
		if (item > now->item ? now->right : now->left)
			btree_insert_data(item > now->item ? &now->right : &now->left, item, cmpf);
		else if (item > now->item)
			now->right = btree_create_node(item);
		else
			now->left = btree_create_node(item);
	}
}
