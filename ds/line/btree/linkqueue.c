#include "linkqueue.h"

link_pqueue init_linkqueue(void){
    link_pqueue q;

    if((q = (link_pqueue)malloc(sizeof(link_queue))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }

    if((q->front = (linkqueue_pnode)malloc(sizeof(linkqueue_node))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    q->front->next = NULL;
    q->rear = q->front;
    return q;
}

bool in_linkqueue(datatype data, link_pqueue q)
{
    linkqueue_pnode new;
    if((new = (linkqueue_pnode)malloc(sizeof(linkqueue_node))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    new->data = data;
    new->next = q->rear->next;
    q->rear->next = new;
    q->rear = q->rear->next;
    return true;
}

bool is_empty_linkqueue(link_pqueue q)
{
    if(q->rear == q->front)
        return true;
    else
        return false;
}
//注意这里和原来函数的不同
btree_pnode out_linkqueue(link_pqueue q)
{
    linkqueue_pnode t;

    if(is_empty_linkqueue(q))
    {
        printf("empty\n");
        return 0;
    }

    t = q->front;
    q->front = q->front->next;
    free(t);
    return q->front->data; 
}

#if 0
void show_linkqueue(link_pqueue q)
{
    linkqueue_pnode p;
        
    for(p=q->front->next; p!=NULL; p=p->next)
    {
        printf("%d ", p->data);
    }
    
    printf("\n");
}

#endif


