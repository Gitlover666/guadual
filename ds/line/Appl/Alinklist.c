#include "Alinklist.h"

//创建一个不带头结点的，就是把H作为开始，参与运算
linklist Alinklist_create()
{
    linklist H, r, q;
    int n, i;
//若输入小于0，则一直输入
loop:
    printf("please input n:");
    scanf("%d", &n);
    if(n < 0)
    {
        printf("n > 0\n");
        goto loop;
    }
	
    if((H = (linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc failed\n");
        return NULL;
    }
	
    H->data = 1;
    H->next = H;
    r = H;
	//从2开始是因为1已经定义了
    for(i=2; i<=n; i++)
    {
        if((q = (linklist)malloc(sizeof(listnode))) == NULL)
        {
            printf("malloc failed\n");
            return NULL;
        }
        q->data = i;
        r->next = q;
        r = q;
    }
	//这里也可以放在循环里面
    q->next = H;
    return H;

}
//实现算法
void Alinklist_jose(linklist H, int k, int m)
{
    linklist p, r;
    int i;

    r = H;
    while(r->next->data != k)
    {
        r= r->next;//这里找的是3前面的2
    }
    printf("k = %d\n", r->next->data);
	//当只剩下自己一个的时候
    while(r->next != r)
    {
        for(i=0; i<m-1; i++)
        {
            r = r->next;
        }
        p = r->next;
        r->next = p->next;
        printf("%d ", p->data);
        free(p);
        p = NULL;
    }
    //之所以在输出一次是因为还剩自己
    printf("%d ", r->data);
    free(r);
    r = NULL;

}

//遍历
void Alinklist_show(linklist H)
{
    linklist p;

    p = H;
    while (p->next != H)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("%d \n", p->data);
}
















