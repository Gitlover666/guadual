//双向循环链表
//只有自己编程才会发现如此多的问题
#include "dlist.h"

int main(int argc, const char *argv[])
{
    dlistnode *H, *p;
    int n;
    H = dlist_create();
    dlist_insert(H, 555, 0);
    dlist_show(H);
 
    printf("input a pos\n");
    scanf("%d", &n);

    p = dlist_get(H, n);
    if(p)
    {
        printf("%d\n", p->data);
    }

    dlist_delete(H, 3);
    dlist_show(H);
    
    return 0;
}
