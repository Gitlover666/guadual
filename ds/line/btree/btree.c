#include "btree.h"
#include "linkqueue.h"
#include "linkstack.h"
//功能：创造一个二叉树
btree_pnode create_tree(void)
{
    datatype_bt ch;
    btree_pnode new;
	//数据自己输入，记得需要#
    scanf("%c", &ch);
	//这里用#代表空
    if(ch == '#')
    {
        return NULL;
    }
    else
    {
		//创造一个二叉树，如果创建失败则退出
        if((new = (btree_pnode)malloc(sizeof(btree_node))) == NULL)
            {
                perror("malloc");
                exit(1);
            }  
		//二叉树的数据节点
        new->data = ch;
		//二叉树的左孩子节点，运用递归
        new->lchild = create_tree();
		//二叉树的右孩子节点，运用递归
        new->rchild = create_tree();
    }
    return new;
}
//先序遍历递归算法
//根据下面三条语句的排列顺序不同，所得的结果不同
void pre_order(btree_pnode t)
{
    if(t != NULL)
    {
        printf("%c", t->data);
        pre_order(t->lchild);
        pre_order(t->rchild);
    }
    
}

//中序遍历递归算法
void mid_order(btree_pnode t)
{
    if(t != NULL)
    {
        mid_order(t->lchild);
        printf("%c", t->data);
        mid_order(t->rchild);
    }
    
}
//后序遍历递归算法
void post_order(btree_pnode t)
{
    if(t != NULL)
    {
        post_order(t->lchild);
        post_order(t->rchild);
        printf("%c", t->data);
    }
    
}
//同一层次非递归队列算法，先进先出
void level_order(btree_pnode t)
{
	//q代表队列变量
    link_pqueue q;
    q = init_linkqueue();
	
    while(t != NULL)
    {
        printf("%c", t->data);
        if(t->lchild != NULL)
			//左孩子入队
            in_linkqueue(t->lchild, q);
        if(t->rchild != NULL)
			//左孩子入队
            in_linkqueue(t->rchild, q);
        if(!is_empty_linkqueue(q))
			//注意这里与原来的队列函数的区别，使用了二叉树类型的t来作为返回数据接收
            t = out_linkqueue(q);
        
        else
            break;
    }
}
//非递归栈算法，先进后出，注意类型匹配
void unpre_order(btree_pnode t)
{
	//创建一个栈变量top；
    linklist top;
    
    top = linkstack_create();
	//当二叉树不为空或者栈不为空的时候执行，注意这里的先后顺序
	//当第一个满足的时候第二个将不再执行
    while (t != NULL || linkstack_empty(top))
    {   
        if(t != NULL)
        {
            printf("%c", t->data);
            if(t->rchild != NULL)
                linkstack_push(top, t->rchild);
            t = t->lchild;
        }
        else{
			//注意这里的返回数据接收问题，困了一个多小时
           t = linkstack_pop(top);
        }
            
    }
}
//实现函数回调，注意这种形式，值得学习，下次查阅时重新学习
void travel(char const *str, void (*fun)(btree_pnode ), btree_pnode t)
{
    printf("%s", str);
    fun(t);
    printf("\n");
}










