#include "dlist.h"
//����һ��˫��ѭ������
dlistnode *dlist_create()
{
    dlistnode * H, * r, * p;
    int n;

    if((H = (dlistnode *)malloc(sizeof(dlistnode))) == NULL)
    {
        printf("malloc failure\n");
        return H;
    }
    //һ��ʼͷ����prior��next��ָ���Լ�
    H->prior = H;
    H->next = H;
    r = H;
    //��������Ȼ���������
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
//������ʾ
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
//����ָ��posλ�õ�����
dlistnode * dlist_get(dlistnode *H, int pos)
{
    int i = -1;
    dlistnode * p = H;

    if(pos < 0)
    {
        printf("pos < 0, invalid\n");
        return NULL;
    }
    //ָ���ҵ�posλ��
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
//��ָ��λ�ò���ָ������value
int dlist_insert(dlistnode *H, int value, int pos)
{
    dlistnode *p, *q;
    p = dlist_get(H, pos);
    if(p == NULL)
    {
        return -1;
    }
    //ע��������Ŀռ���Ҫ�ж�һ��
    if((q = (dlistnode *)malloc(sizeof(dlistnode))) == NULL)
        {
            printf("malloc failure\n");
            return -1;
        }
    //q�ռ�����ʢ�Ų�������
    q->data = value;

    q->prior = p->prior;
    q->next = p;
    p->prior->next = q;
    p->prior = q;
    
    return 0;

}
//ɾ��ָ��λ�õ�����
int dlist_delete(dlistnode *H, int pos)
{
    dlistnode * p;
    //��ø�����
    p = dlist_get(H, pos);
    if (p == NULL)
    {
        return -1;
    }
    //��p�ռ��ͷ�
    p->prior->next = p->next;
    p->next->prior = p->prior;  
    free(p); 
    p = NULL;

    return 0;
}


