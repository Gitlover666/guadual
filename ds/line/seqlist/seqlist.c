#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"
//创建一个顺序表
seqlist_t *create_seqlist(void)
{
    seqlist_t *L = NULL;//清空
    L = (seqlist_t *)malloc(sizeof(seqlist_t));//分配空间
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("no memory\n");
        return NULL;
    }
    L->last = -1;//一开始让其指向-1
    return L;
}
//清空释放顺序表
void clear_seqlist(seqlist_t *L)
{
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return ;
    }
    free(L);
    return ;
}
//判断是否为空
int is_empty_seqklist(seqlist_t *L)
{
   if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
    return (L->last == -1);
}
//判断是否满
int is_full_seqklist(seqlist_t *L)
{
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
    return (L->last == MAXSIZE - 1);
}
//遍历显示顺序表
void show_seqlist(seqlist_t *L)
{
    int i = 0;
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return ;
    }
    for(i=0; i<=L->last; i++)  
        printf("L->data[%d] = %d\n", i, L->data[i]);
    return ;
}
//顺序表插入
int insert_seqlist(seqlist_t *L, data_t x, int pos)
{
    int i = 0;
    if((is_full_seqklist(L))||(pos<0)||(pos>L->last + 1))//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
	//这里的操作是避免信息覆盖，所以使其插入点的信息依次后移
    for(i=L->last; i>=pos; i--)
        L->data[i+1] = L->data[i];
	//准备完毕开始赋值
    L->data[pos] = x;
	//必须要加一
    L->last++;
    return 0;
}
//建立一个空顺序表
void set_empty_seqlist(seqlist_t *L)
{
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return;
    }
	//表示为空
    L->last = -1;
    return;
}

int delete_seqlist(seqlist_t *L, int pos)
{
    int i = 0;
    //测试发现卡可以不加一
    //if((pos<0)||(pos>L->last+1))
    if((pos<0)||(pos>L->last))
    {
        puts("input pos is invalid\n");
        return -1;
    }
	//用后面的数据依次代替前面的数据
    for(i=pos; i<=L->last; i++)
        L->data[i] = L->data[i+1];
	//必须减一，代表顺序表最大位少一
    L->last--;
    return 0;
}
//改变顺序表某一位
int change_seqlist(seqlist_t *L, data_t x, int pos)
{
	//个人认为这里没有必要加一
   // if((pos<0)||(pos>L->last + 1))
	if((pos<0)||(pos>L->last))
    {
        puts("input pos is invalid\n");
        return -1;
    }
    L->data[pos] = x;
    return 0;
}
//根据值来寻找
int search_seqlist(seqlist_t *L, data_t x)
{
    int i = 0;
    for(i=0; i<L->last; i++)
    {
        if(L->data[i] == x)
            return i;
    }
    return -1;
}

//当前顺序表的长度
int get_length_seqlist(seqlist_t *L)
{
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
    return (L->last + 1);
}



