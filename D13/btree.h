#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct			s_btree
{
	struct s_btree		*father;
	struct s_btree		*left;
	struct s_btree		*right;
	int					item;
}						t_btree;

t_btree *btree_create_node(int item);
void btree_apply_prefix(t_btree *root, void (*applyf)(int));
void btree_apply_infix(t_btree *root, void (*applyf)(int));
void btree_apply_suffix(t_btree *root, void (*applyf)(int));
void btree_insert_data(t_btree **root, int item, int (*cmpf)(int, int));
void f(int x);
int cmp(int a, int b);
