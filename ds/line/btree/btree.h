#ifndef _BTREE_H
#define _BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef char datatype_bt;
typedef struct btreenode{
    datatype_bt data;
    struct btreenode *lchild, *rchild;
}btree_node, *btree_pnode;

btree_pnode create_tree(void);
void pre_order(btree_pnode t);
void mid_order(btree_pnode t);
void post_order(btree_pnode t);
void level_order(btree_pnode t);
void unpre_order(btree_pnode t);
void travel(char const *str, void (*fun)(btree_pnode ), btree_pnode t);
#endif 
