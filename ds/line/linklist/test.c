#include "linklist.h"

int main(int argc, const char* argv[])
{
    linklist H;
    int n;

    H = list_create();
    list_head_insert(H, 10);
    list_head_insert(H, 20);
    list_head_insert(H, 30);
    list_head_insert(H, 40);
    list_show(H);
    printf("please input a pos\n");
    scanf("%d", &n);
//    if((H = list_get(H, n)) != NULL)
  //      printf("%d\n", H->data);
//    H = list_create1();
//    if((H = list_locate(H, n)) != NULL)
 //       printf("%d\n", H->data);
 //     if((list_insert(H, n, 100)) == -1)
  //        printf("error");
    if((list_delete(H, n))== -1)
    {
        printf("error");
    }
    list_show(H);
    list_reverse(H);
    list_sort(H);
    list_show(H);
    return 0;
}











