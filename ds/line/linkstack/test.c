#include "linkstack.h"

int main(int argc, const char* argv[])
{
    linklist s;

    s = linkstack_create();

    linkstack_push(s, 10);
    linkstack_push(s, 20);
    linkstack_push(s, 30);
    linkstack_push(s, 40);
    linkstack_pop(s);
    linkstack_free(s);
    return 0;

}