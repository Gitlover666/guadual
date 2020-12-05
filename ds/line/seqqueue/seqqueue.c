//先进先出
#include "seqqueue.h"
//循环队列创建初始化
seq_pqueue init_seqqueue(void){
    seq_pqueue q;

    if((q = (seq_pqueue)malloc(sizeof(seq_queue))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    //这里指向末尾，数字最大
    q->front = q->rear = MAXSIZE - 1;

    return q;
}
//判断是否满队
bool is_full_seqqueue(seq_pqueue q)
{
    //判断尾端是否与头部重合，若重合则满队
    if((q->rear+1)%MAXSIZE == q->front)
        return true;
    else
    {
        return false;
    }   
}
//入队
bool in_seqqueue(datatype data, seq_pqueue q)
{
    if(is_full_seqqueue(q))
    {
        printf("full\n");
        return false;
    }
    //如果不满则入队，% MAXSIZE能够很好的保证队列实现循环效果
    q->rear = (q->rear + 1) % MAXSIZE;
    q->data[q->rear] = data;
    return true;
}
//判空
bool is_empty_seqqueue(seq_pqueue q)
{
    if(q->rear == q->front)
        return true;
    else
        return false;
}
//出队
bool out_seqqueue(seq_pqueue q)
{
    if(is_empty_seqqueue(q))
    {
        printf("empty\n");
        return false;
    }
    //先进先出，控制范围
    q->front =(q->front + 1) % MAXSIZE;
    printf("%d \n", q->data[q->front]);
    
    return true; 
}
//遍历
void show_seqqueue(seq_pqueue q)
{
    int i;
    if(is_empty_seqqueue(q))
        return ;
        //通过这个循环可以实现，遍历输出
        for(i=(q->front+1)%MAXSIZE; i!=(q->rear+1)%MAXSIZE; i=(i+1)%MAXSIZE)
        {
            printf("%d ", q->data[i]);
        }
    
    printf("\n");
}




