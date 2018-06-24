#include "../btree.h"

void btree_insert_data(t_btree **root, int item, int (*cmpf)(int, int))
{
	t_btree		*now;

	if (!(*root))
		*root = btree_create_node(item);
	else
	{
		now = *root;
//		while (item > now->item ? now->right : now->left)
		while (cmpf(now->item, item) == -1 ? now->right : now->left)
			now = item > now->item ? now->right : now->left;
		if (cmpf(now->item, item) == -1)
//		if (item > now->item)
			now->right = btree_create_node(item);
		else
			now->left = btree_create_node(item);
	}
}
