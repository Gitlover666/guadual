//ջ�㷨
#include "sqstack.h"

int main(int argc, const char* argv[])
{
    sqstack * s;
    int n = 5;

    s = stack_create(n);

    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);
    stack_push(s, 40);
    stack_push(s, 60);
    printf("%d\n", stack_top(s));
    stack_clear(s);
    stack_pop(s);

    stack_free(s);
}