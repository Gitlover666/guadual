#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"
//创建一个s顺序表
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

int is_empty_seqklist(seqlist_t *L)
{
   if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
    return (L->last == -1);
}
int is_full_seqklist(seqlist_t *L)
{
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
    return (L->last == MAXSIZE - 1);
}

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

int insert_seqlist(seqlist_t *L, data_t x, int pos)
{
    int i = 0;
    if((is_full_seqklist(L))||(pos<0)||(pos>L->last + 1))//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
    for(i=L->last; i>=pos; i--)
        L->data[i+1] = L->data[i];
    L->data[pos] = x;
    L->last++;
    return 0;
}

void set_empty_seqlist(seqlist_t *L)
{
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return;
    }
    L->last = -1;
    return;
}

int delete_seqlist(seqlist_t *L, int pos)
{
    int i = 0;
    if((pos<0)||(pos>L->last+1))
    {
        puts("input pos is invalid\n");
        return -1;
    }
    for(i=pos; i<=L->last; i++)
        L->data[i] = L->data[i+1];
    L->last--;
    return 0;
}

int change_seqlist(seqlist_t *L, data_t x, int pos)
{
    if((pos<0)||(pos>L->last + 1))
    {
        puts("input pos is invalid\n");
        return -1;
    }
    L->data[pos] = x;
    return 0;
}
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


int get_length_seqlist(seqlist_t *L)
{
    if(L == NULL)//如果创建为空，返回信息
    {
        puts("seqlist_t *L is NULL\n");
        return -1;
    }
    return (L->last + 1);
}



