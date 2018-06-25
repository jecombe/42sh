#include "../btree.h"

int btree_search_item(t_btree *root, int data, int (*cmpf)(int, int))
{
	if (root->item == data)
		return (root->item);
	else if (data > root->item && root->right)
		return (0 + btree_search_item(root->right, data, cmpf));
	else if (root->left)
		return (0 + btree_search_item(root->left, data, cmpf));
	else
		return (0);
}
