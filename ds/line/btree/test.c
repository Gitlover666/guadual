#include "btree.h"

int main()
{
    btree_pnode t;
    
    t = create_tree();

    printf("xianxu\n");
    pre_order(t);
    printf("\n");

    printf("midxu\n");
    mid_order(t);
    printf("\n");

    printf("postxu\n");
    post_order(t);
    printf("\n");

    printf("postxu\n");
    level_order(t);
    printf("\n");

    printf("postxu\n");
    unpre_order(t);
    printf("\n");
    //调用回调函数
    travel("xian",pre_order , t);
    travel("xian",mid_order , t);
    travel("xian",post_order , t);
    travel("xian",level_order , t);
    travel("xian",unpre_order , t);

    return 0;
}























