#include "linkqueue.h"
//��ʼ�����ߴ���ѭ����������ʽ����
link_pqueue init_linkqueue(void){
    link_pqueue q;

    if((q = (link_pqueue)malloc(sizeof(link_queue))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    //����ഴ����һ����̬�ռ�������Ŷ�������
    if((q->front = (linkqueue_pnode)malloc(sizeof(linkqueue_node))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    q->front->next = NULL;
    //��ֵ��ͷ����β������һ���ռ�
    q->rear = q->front;
    return q;
}
//bool����ֻ������1��0���������
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
//�ж�ѭ������������Ƿ�Ϊ��
bool is_empty_linkqueue(link_pqueue q)
{
    //���qͷ��ָ��β�����
    if(q->rear == q->front)
        return true;
    else
        return false;
}
//����
bool out_linkqueue(link_pqueue q)
{   
    //֮������linkqueue_pnode���Ϳ������Ϊ��link_pqueue���ӿռ䣬�����в������������ӿռ���е�
    linkqueue_pnode t;

    if(is_empty_linkqueue(q))
    {
        printf("empty\n");
        return false;
    }
    //���ͷ�ͷ�ռ䣬�������0������
    t = q->front;
    q->front = q->front->next;
    printf("%d \n", q->front->data);
    free(t);
    return true; 
}
//�������
void show_linkqueue(link_pqueue q)
{
    linkqueue_pnode p;
        
    for(p=q->front->next; p!=NULL; p=p->next)
    {
        printf("%d ", p->data);
    }
    
    printf("\n");
}




