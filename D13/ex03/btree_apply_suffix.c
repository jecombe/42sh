#include "../btree.h"

void btree_apply_suffix(t_btree *root, void (*f)(int))
{
	if (root->left)
		btree_apply_suffix(root->left, f);
	if (root->right)
		btree_apply_suffix(root->right, f);
	f(root->item);
}
