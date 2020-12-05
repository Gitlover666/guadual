//�Ƚ��ȳ�
#include "seqqueue.h"
//ѭ�����д�����ʼ��
seq_pqueue init_seqqueue(void){
    seq_pqueue q;

    if((q = (seq_pqueue)malloc(sizeof(seq_queue))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    //����ָ��ĩβ���������
    q->front = q->rear = MAXSIZE - 1;

    return q;
}
//�ж��Ƿ�����
bool is_full_seqqueue(seq_pqueue q)
{
    //�ж�β���Ƿ���ͷ���غϣ����غ�������
    if((q->rear+1)%MAXSIZE == q->front)
        return true;
    else
    {
        return false;
    }   
}
//���
bool in_seqqueue(datatype data, seq_pqueue q)
{
    if(is_full_seqqueue(q))
    {
        printf("full\n");
        return false;
    }
    //�����������ӣ�% MAXSIZE�ܹ��ܺõı�֤����ʵ��ѭ��Ч��
    q->rear = (q->rear + 1) % MAXSIZE;
    q->data[q->rear] = data;
    return true;
}
//�п�
bool is_empty_seqqueue(seq_pqueue q)
{
    if(q->rear == q->front)
        return true;
    else
        return false;
}
//����
bool out_seqqueue(seq_pqueue q)
{
    if(is_empty_seqqueue(q))
    {
        printf("empty\n");
        return false;
    }
    //�Ƚ��ȳ������Ʒ�Χ
    q->front =(q->front + 1) % MAXSIZE;
    printf("%d \n", q->data[q->front]);
    
    return true; 
}
//����
void show_seqqueue(seq_pqueue q)
{
    int i;
    if(is_empty_seqqueue(q))
        return ;
        //ͨ�����ѭ������ʵ�֣��������
        for(i=(q->front+1)%MAXSIZE; i!=(q->rear+1)%MAXSIZE; i=(i+1)%MAXSIZE)
        {
            printf("%d ", q->data[i]);
        }
    
    printf("\n");
}




