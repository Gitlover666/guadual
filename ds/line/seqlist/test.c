#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"

int main(int argc, const char *argv[])
{
    /*
    int i = 0;
    seqlist_t *L = NULL;
    L = create_seqlist();
    for(i=0; i<=4; i++)
        insert_seqlist(L, i, 0);
    show_seqlist(L);
    return 0;
    */
    int i = 0;
    seqlist_t *L = NULL;
    L = create_seqlist();
    for(i=0; i<=4; i++)
        insert_seqlist(L, i, 0);
    printf("length is %d\n", get_length_seqlist(L));
    show_seqlist(L);
    puts("================================");
    puts("search data = 3");
    printf("data = 3 pos is %d\n", search_seqlist(L, 3));
    printf("seqlist L length is %d\n", get_length_seqlist(L));
    show_seqlist(L);
    puts("================================");
    puts("search data = 3");
    delete_seqlist(L, search_seqlist(L, 3));
    printf("seqlist L length is %d\n", get_length_seqlist(L));
    show_seqlist(L);
    puts("================================");
    puts("change data[2] = 99\n");
    change_seqlist(L, 99, 2);
    printf("seqlist L length is %d\n", get_length_seqlist(L));
    show_seqlist(L);
    puts("================================");
    delete_seqlist(L, 4);

    show_seqlist(L);
    clear_seqlist(L);
    
    return 0;


}


