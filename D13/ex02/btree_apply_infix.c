#include "../btree.h"

void btree_apply_infix(t_btree *root, void (*f)(int))
{
	if (root->left)
		btree_apply_infix(root->left, f);
	f(root->item);
	if (root->right)
		btree_apply_infix(root->right, f);
}
