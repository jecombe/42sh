#include "../btree.h"

void btree_apply_prefix(t_btree *root, void (*applyf)(int))
{
	f(root->item);
	if (root->left)
		btree_apply_prefix(root->left, f);
	if (root->right)
		btree_apply_prefix(root->right, f);
}
