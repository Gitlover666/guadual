//循环单链表形式的队列
#include "linkqueue.h"

int main(void)
{
    link_pqueue q;
    datatype data;
    int ret;

    q = init_linkqueue();

    while(1)
    {
        printf("111\n");
        ret = scanf("%d", &data);

        if(ret == 1)
        {
            if(in_linkqueue(data, q))
                show_linkqueue(q);
        }
        else
        {
            if(out_linkqueue(q))
                show_linkqueue(q);
        }
        while(getchar() != '\n');
    }

 return 0;
}