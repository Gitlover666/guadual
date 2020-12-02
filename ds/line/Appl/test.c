//循环链表的应用，数中走人
#include "Alinklist.h"


int main(int argc, const char* argv[])
{
    linklist H;
    int k = 3, m = 4;
    //当m=1时，数到谁就出来

    H = Alinklist_create();
    Alinklist_show(H);

    Alinklist_jose(H, k, m);
    
    return 0;
}


