#include "sqstack.h"
//����һ��ջ
sqstack * stack_create(int len)
{
    sqstack * s;

    if((s = (sqstack *)malloc((sizeof(sqstack)))) == NULL){
        printf("malloce prror\n");        
        return NULL;
    }
    //ջ���ݴ�������
    if((s->data = (datatype *)malloc(sizeof(datatype) * len)) == NULL){
        printf("malloce prror\n");        
        return NULL;
    }

    s->maxlen = len;
    //����һ��ʼ ����Ϊ-1��һ��ʼ��������Ϊ0��������������ֵ����Ӱ��
    s->top = -1;
    return s;
}
//�ж�ջ��
int stack_empty(sqstack * s)
{
    return (s->top == -1 ? 1 : 0);
}
//���ջֱ����ͷ��ָ�����λ�ã��������ݻ�����ʹ�ñ�����
void stack_clear(sqstack * s)
{
    
    s->top = -1;
}
//ջ��
int stack_full(sqstack * s)
{
    return (s->top == s->maxlen-1 ? 1 : 0);
}
//��ջ
int stack_push(sqstack * s, datatype value)
{
    if(s->top == s->maxlen - 1)
    {
        printf("stack is full\n");
        return 0;
    }
    //��0��ʼ��ջ
    s->data[s->top+1] = value;
    s->top++;
    
    return 1;

}
//��ջ
datatype stack_pop(sqstack * s)
{
    while(s->top != -1)
    {
        printf("%d\n", s->data[s->top]);
        s->top--;
    }

    return 1;
}
//��ȡջ��λ��
datatype stack_top(sqstack * s)
{
    return s->data[s->top];
}
//�ͷ��ڴ�
void stack_free(sqstack * s)
{
    free(s->data);
    s->data = NULL;
    free(s);
    s = NULL;
}








