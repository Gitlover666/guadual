#include "linkstack.h"

linklist linkstack_create()
{
    linklist s;
    if ((s = (linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc failure\n");
        return NULL;
    }

    s->next = NULL;
    return s;
}

int linkstack_empty(linklist s)
{

    return (s->next == NULL ? 0 : 1);
}
//每次入栈都重新开辟一个动态空间，相当于重新插入
int linkstack_push(linklist s, datatype1 data)
{

    linklist p;
    if ((p = (linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc failure\n");
        return -1;
    }

    p->data = data;
    p->next = s->next;
    s->next = p;

    return 0;
}
/****************************************************************************************
这里和前面学的单链表不一样是因为，而且前面入栈的时候，每入栈一次都申请了一次空间，
所以每次都需要free这里出栈相当于把这个位置清空，把数据取出来，
而单链表并不改变链表
****************************************************************************************/
datatype1 linkstack_pop(linklist s)
{
    linklist p;
    btree_pnode ret;
    p = s->next;
    s->next = p->next;
    ret = p->data;
    free(p);
    p = NULL;

    return ret;
}

datatype1 linkstack_top(linklist s)
{
    return s->next->data;
}
//清空的话不包括头结点
void linkstack_clear(linklist s)
{
    linklist p;

    p = s->next;
    while (p)
    {
        s->next = p->next;

        free(p);
        p = s->next;
    }
}
//这里把头结点也释放
void linkstack_free(linklist s)
{
    linklist p;

    printf("free\n");
    p = s;
    while (p)
    {
        s = s->next;

        free(p);
        p = s;
    }
}
