//—≠ª∑∂”¡–
#include "seqqueue.h"

int main(void)
{
    seq_pqueue q;
    datatype data;
    int ret;

    q = init_seqqueue();

    while(1)
    {
        printf("111\n");
        ret = scanf("%d", &data);

        if(ret == 1)
        {
            if(in_seqqueue(data, q))
                show_seqqueue(q);
        }
        else
        {
            if(out_seqqueue(q))
                show_seqqueue(q);
        }
        while(getchar() != '\n');
    }

 return 0;
}