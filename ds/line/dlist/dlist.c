#include "dlist.h"
//创建一个双向循环链表
dlistnode *dlist_create()
{
    dlistnode * H, * r, * p;
    int n;

    if((H = (dlistnode *)malloc(sizeof(dlistnode))) == NULL)
    {
        printf("malloc failure\n");
        return H;
    }
    //一开始头部的prior和next都指向自己
    H->prior = H;
    H->next = H;
    r = H;
    //输入数据然后进入链表
    while(1)
    {
        printf("please input a number(-1 exit):");
        scanf("%d",&n);
        if(n == -1)
            break;
        
        if((p = (dlistnode *)malloc(sizeof(dlistnode))) == NULL)
        {
            printf("malloc failure\n");
            return NULL;
        }

        p->data = n;

        p->prior = r;
        p->next = r->next;
        r->next = p;
        H->prior = p;
        r = p;
    }
    return H;
}
//遍历显示
void dlist_show(dlistnode *H)
{
    dlistnode * p;
    p = H->next;

    while (p != H)
    {
        printf("%d ",p->data);
        p = p->next;
    }

}
//查找指定pos位置的数据
dlistnode * dlist_get(dlistnode *H, int pos)
{
    int i = -1;
    dlistnode * p = H;

    if(pos < 0)
    {
        printf("pos < 0, invalid\n");
        return NULL;
    }
    //指导找到pos位置
    while(i < pos)
    {
        p = p->next;
        i++;
        if(p == H)
        {
            printf("pos is invalid\n");
            return NULL;
        }
    }
    return p;
}
//在指定位置插入指定数据value
int dlist_insert(dlistnode *H, int value, int pos)
{
    dlistnode *p, *q;
    p = dlist_get(H, pos);
    if(p == NULL)
    {
        return -1;
    }
    //注意新申请的空间需要判断一下
    if((q = (dlistnode *)malloc(sizeof(dlistnode))) == NULL)
        {
            printf("malloc failure\n");
            return -1;
        }
    //q空间用来盛放插入数据
    q->data = value;

    q->prior = p->prior;
    q->next = p;
    p->prior->next = q;
    p->prior = q;
    
    return 0;

}
//删除指定位置的数据
int dlist_delete(dlistnode *H, int pos)
{
    dlistnode * p;
    //获得该数据
    p = dlist_get(H, pos);
    if (p == NULL)
    {
        return -1;
    }
    //把p空间释放
    p->prior->next = p->next;
    p->next->prior = p->prior;  
    free(p); 
    p = NULL;

    return 0;
}


