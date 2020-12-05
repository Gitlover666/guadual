#include "sqstack.h"
//创建一个栈
sqstack * stack_create(int len)
{
    sqstack * s;

    if((s = (sqstack *)malloc((sizeof(sqstack)))) == NULL){
        printf("malloce prror\n");        
        return NULL;
    }
    //栈数据存在这里
    if((s->data = (datatype *)malloc(sizeof(datatype) * len)) == NULL){
        printf("malloce prror\n");        
        return NULL;
    }

    s->maxlen = len;
    //顶部一开始 设置为-1，一开始不能设置为0，可能里面有数值，会影响
    s->top = -1;
    return s;
}
//判断栈空
int stack_empty(sqstack * s)
{
    return (s->top == -1 ? 1 : 0);
}
//清空栈直接人头部指向起点位置，其余数据会随着使用被覆盖
void stack_clear(sqstack * s)
{
    
    s->top = -1;
}
//栈满
int stack_full(sqstack * s)
{
    return (s->top == s->maxlen-1 ? 1 : 0);
}
//入栈
int stack_push(sqstack * s, datatype value)
{
    if(s->top == s->maxlen - 1)
    {
        printf("stack is full\n");
        return 0;
    }
    //从0开始入栈
    s->data[s->top+1] = value;
    s->top++;
    
    return 1;

}
//出栈
datatype stack_pop(sqstack * s)
{
    while(s->top != -1)
    {
        printf("%d\n", s->data[s->top]);
        s->top--;
    }

    return 1;
}
//获取栈顶位置
datatype stack_top(sqstack * s)
{
    return s->data[s->top];
}
//释放内存
void stack_free(sqstack * s)
{
    free(s->data);
    s->data = NULL;
    free(s);
    s = NULL;
}








