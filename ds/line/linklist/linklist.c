/******************************************************
		            单链表
				  2020-11-22
******************************************************/
#include "linklist.h"
/******************************************************
		           创建单链表
******************************************************/
linklist list_create()
{
    linklist H;
	//使用前必须给单链表分配一个动态空间
    if((H =(linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc failure\n");
        return NULL;
    }
	//这里使用了一个头部，也可以不使用
    H->data = 0;
    H->next = NULL;
    return H;
}
/******************************************************
		           遍历显示单链表
******************************************************/
void list_show(linklist H)
{
	//设置一个循环，当其出现NULL 时说明遍历完成，尾部为空
    while(H->next)
    {
        printf("%d ", H->next->data);
        H = H->next;
    }
    printf("\n");
}
/******************************************************
		      根据所给位置找
******************************************************/
linklist list_get(linklist H, int pos)
{
    linklist p = H;
	//为-1是因为有0号元素
    int i = -1;
	
    if(pos < 0)
    {
        printf("position is invalid:<0 \n");
        return NULL;
    }
	//利用p = p->next;实现一个动态查询
	//第一种方法
    while(p->next && i < pos)
    {
        p = p->next;
        i++;
    }
	//循环结束后判断是否找到
    if(i == pos)
        return p;
    else
    {
        printf("position is invalid:>length\n");
        return NULL;
    }
}
/******************************************************
		      根据所给值来找
******************************************************/
linklist list_locate(linklist H, int value)
{
    linklist p = H->next;//从下一个也就是地0位开始
	//这种方法和第一种结果应该差不多
    while(p && p->data != value)
    {    
        p = p->next; 
    }
    return p;
}
/******************************************************
		      在任意位置前面插入任意值
******************************************************/
int list_insert(linklist H,int pos, datatype value)
{
	//定义两个结构体指针变量
    linklist p, q;
	//先判断是否为零，为零时直接赋值H，因为零位的前面是头部，否则
    if(pos == 0)
        p = H;
    else
    {
		//之所以pos-1是根据这个函数来使用的
		//也就是说pos等于1，这里找到的是第零位，然后对其后面插入
        p = list_get(H, pos-1);
    }
    
    if(p == NULL)
    {
        printf("para is invalid \n");
        return -1;
    }
    else
    {   
		//需要重新给q开辟一个动态空间，否则报错
        if((q =(linklist)malloc(sizeof(listnode))) == NULL)
        {
            printf("malloc failure\n");
            return -1;
        }
		
        q->data = value;
        q->next = p->next;
        p->next = q;
        return 0;
    }  
}

/******************************************************
		      在头部插入
******************************************************/
int list_head_insert(linklist H, datatype value)
{
    linklist p;

    if((p =(linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc failure\n");
        return -1;
    }
	//这种形式挺常用
    p->data = value;
    p->next = H->next;
    H->next = p;
    
    return 0;
}
/******************************************************
		     删除某一位置
注意需要free
******************************************************/
int list_delete(linklist H, int pos)
{
    linklist p, q;
    if(pos == 0)
        p = H;
    else
    {
		//注意这里是pos-1
        p = list_get(H, pos-1);
    }
    
    if(p== NULL || p->next == NULL)
    {
        printf("para is invalid \n");
        return -1;
    }
    else
    {   
        q = p->next;
        p->next = q->next;
		//这两步操作必须有，不然会造成内存泄漏和野指针
        free(q);
        q = NULL;
        return 0;
    }  
}
/******************************************************
		      顺序倒置
******************************************************/
void list_reverse(linklist H)
{
    linklist p, q;

    p = H->next;
	//置空相当于H后面的链子断掉
    H->next = NULL;

    while(p)
    {
		//不要纠结，只是学习加使用，后续慢慢理解
        q = p;
        p = p->next;

        q->next = H->next;
        H->next = q;
    }
}
/******************************************************
				排序插入
******************************************************/
int list_order_insert(linklist H, datatype value)
{
    linklist p, q;
    q = H;
	//一般开辟一个新的动态空间都是用来保存不在链子当中的或者从链子当中下来的内容
    if((p =(linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc failure\n");
        return -1;
    }
    p->data = value;
	//只要q->next不为空，且其下一个数值小于value则继续遍历
    while (q->next && q->next->data < value)
    {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;

    return 0;
}
/******************************************************
				从小到大排序
******************************************************/
void list_sort(linklist H)
{
    linklist q, p, r;

    p = H->next;
    H->next = NULL;

    while(p)
    {
        q = p;
        p = p->next;
        r = H;
		//判断是否为空同时一直判断其数值是否小于q->data
        while(r->next && (r->next->data < q->data))
        {
            r = r->next;
        }
        q->next = r->next;
        r->next = q;
    }
}
/******************************************************
				用户输入创造链表
******************************************************/
linklist list_create1()
{
    linklist r, p, H;
    int value;

    if((H =(linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc failure\n");
        return H;
    }

    H->data = 0;
    H->next = NULL;
    r = H;

    while(1)
    {
        printf("input a number(-1 exit)");
        scanf("%d", &value);
        if(value == -1)
            break;
        if((p =(linklist)malloc(sizeof(listnode))) == NULL)
        {
            printf("malloc failure\n");
            return p;
        }
        p->data = value;
        p->next = NULL;
		//下面两句实现移动
        r->next = p;
        r = p;
        //r 操作完以后返回的是H，说明是有分身功能,这是规定
    }
    return H; 
}


















