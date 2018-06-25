#include "./btree.h"

int		main(int ac, char **av)
{
	t_btree		*root;
	t_btree		*new;
	t_btree		*now;
	int			i = 0;
	int			j;

	root = NULL;
	while (av[++i])
	{
		j = atoi(av[i]);
		btree_insert_data(&root, j, cmp);
	}
	printf("%d\n", btree_search_item(root, 42, cmp));
/*	printf("ROOT->ITEM == %d\n", root->item);
	printf("ROOT->LEFT->ITEM == %d\n", root->left->item);
	printf("ROOT->LEFT->LEFT->ITEM == %d\n", root->left->left->item);
	printf("ROOT->LEFT->RIGHT->ITEM == %d\n", root->left->right->item);
	printf("ROOT->RIGHT->ITEM == %d\n", root->right->item);
	printf("ROOT->RIGHT->LEFT->ITEM == %d\n", root->right->left->item);
	printf("ROOT->RIGHT->LEFT->RIGHT->ITEM == %d\n", root->right->left->right->item);
	printf("ROOT->RIGHT->RIGHT->ITEM == %d\n", root->right->right->item);
	printf("ROOT->RIGHT->RIGHT->RIGHT->ITEM == %d\n", root->right->right->right->item);*/
	return (0);
}
