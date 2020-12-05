#include "linkqueue.h"
//初始化或者创建循环单链表形式队列
link_pqueue init_linkqueue(void){
    link_pqueue q;

    if((q = (link_pqueue)malloc(sizeof(link_queue))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    //这里多创建了一个动态空间用来存放队列数据
    if((q->front = (linkqueue_pnode)malloc(sizeof(linkqueue_node))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    q->front->next = NULL;
    //赋值后头部和尾部都有一个空间
    q->rear = q->front;
    return q;
}
//bool类型只返回真1假0，存放数据
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
//判断循环单链表队列是否为空
bool is_empty_linkqueue(link_pqueue q)
{
    //如果q头部指向尾部则空
    if(q->rear == q->front)
        return true;
    else
        return false;
}
//出队
bool out_linkqueue(link_pqueue q)
{   
    //之所以是linkqueue_pnode类型可以理解为是link_pqueue的子空间，而队列操作都是在其子空间进行的
    linkqueue_pnode t;

    if(is_empty_linkqueue(q))
    {
        printf("empty\n");
        return false;
    }
    //先释放头空间，输出的是0号数据
    t = q->front;
    q->front = q->front->next;
    printf("%d \n", q->front->data);
    free(t);
    return true; 
}
//遍历输出
void show_linkqueue(link_pqueue q)
{
    linkqueue_pnode p;
        
    for(p=q->front->next; p!=NULL; p=p->next)
    {
        printf("%d ", p->data);
    }
    
    printf("\n");
}




