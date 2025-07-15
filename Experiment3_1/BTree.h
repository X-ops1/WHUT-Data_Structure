#ifndef __BTREE_H__
#define __BTREE_H__
#include <iostream>
#include "Stack.h"
using namespace std;
#define MaxSize 100
template<class ElemType>
class BTree
{
private:
    //树的结构体定义
    typedef struct node
    {
        ElemType data;//树的结点值
        struct node* lchild;//树节点左孩子
        struct node* rchild;//树节点右孩子
    }BTNode;
    BTNode* b;//根节点

public:
    BTNode* GetRoot()
    {
        return b;
    }
    BTree(std::string str)//根据括号表示法初始化树
    {
        b=nullptr;
        Stack<BTNode> st;
        BTNode* p;
        bool flag=true;
        int i=0;
        while(i<str.length())
        {
            switch(str[i])
            {
                case '(':
                    st.Push(p);//刚刚新建的结点有孩子，将其进栈
                    flag=true;
                    break;
                case ')'://栈顶结点的子树处理完，出栈
                    st.Pop(p);
                    break;
                case ',':
                    flag=false;//开始处理栈顶结点右孩子
                    break;
                default:
                    p = new BTNode();
                    p->data=str[i];
                    if(b==NULL)
                        b=p;//如果根结点还没有被赋值，则将根结点赋值
                    else
                    {
                        BTNode* q;
                        st.GetTop(q);
                        if(flag&&!st.StackEmpty())//新结点p为栈顶结点的左孩子
                            q->lchild=p;
                        else if(!st.StackEmpty())//新结点p为栈顶结点的右孩子
                            q->rchild=p;
                    }
                    break;
            }
            i++;
        }
    }
    ~BTree(){
        DestoryBTree(b);
    }
    void PostOrder(BTNode *b)//后续遍历递归算法
    {
        if(b!=NULL)
        {
            PostOrder(b->lchild);
            PostOrder(b->rchild);
            cout<<b->data;
        }
    }
    void PostOrderRe(BTNode* b)//后续遍历非递归算法
    {
        BTNode* p=b,*pre=NULL;
        Stack<BTNode> st;
        while(p!=NULL||!st.StackEmpty())
        {
            if(p!=NULL)//扫描p的所有左下结点并进栈
            {
                st.Push(p);
                p=p->lchild;
            }
            else
            {
                st.GetTop(p);//取出当前栈的顶点
                if(p->rchild&&p->rchild!=pre)//如果右子树存在并且没有被访问
                {
                    p=p->rchild;
                }
                else
                {
                    st.Pop(p);
                    cout<<p->data;//访问结点
                    pre=p;//用pre记录刚刚访问过的结点
                    p=NULL;//结点访问完重置p指针
                }

            }
        }
    }
    void PreOrderRe(BTNode* b)//先序遍历非递归算法
    {
        BTNode *p=b;
        Stack<BTNode> st;
        while(p!=NULL||!st.StackEmpty())
        {
            if(p!=NULL)
            {
                cout<<p->data;
                st.Push(p);
                p=p->lchild;
            }
            else
            {
                st.Pop(p);
                p=p->rchild;
            }
        }
    }
    void FindAllAncestor(char object)//输出结点object的所有长辈
    {
        Stack<BTNode> stack;//辅助栈，用于追踪路径
        BTNode *p=b,*r;//从根结点开始,r为空或指定上一步访问的节点元素
        bool flag;//标记是否右子树进栈
        do
        {
            while(p!=NULL)//将p节点的所有左子树入栈
            {
                stack.Push(p);
                p=p->lchild;
            }
            r=NULL;
            flag=true;
            while(!stack.StackEmpty()&&flag)
            {
                stack.GetTop(p);
                if(p->rchild==r)//如果右子树为空或者已经访问过
                {
                    if(p->data==object)//如果当前元素为要查找的成员
                    {
                        bool flag_ancestor=false;//用来标记下层的右子树，因为右子树代表兄弟
                        int i=stack.GetNum();
                        while(!flag_ancestor&&i>0)//用于去掉下层以右子树连接的元素
                        {
                            if(stack.GetElement(i-1)->lchild!=nullptr)
                            {
                                if(stack.GetElement(i-1)->lchild->data==stack.GetElement(i)->data)
                                    flag_ancestor=true;
                            }
                            i--;
                        }//调用ShwoAncestor()输出栈中剩余元素及同辈
                        while(i>-1&&flag_ancestor)
                        {
                            ShowAncestor(stack.GetElement(i));
                            i--;
                        }
                    }
                    stack.Pop(p);
                    r=p;
                }//将右子树入栈
                else
                {
                    p=p->rchild;
                    flag=false;
                }
            }
        }while(!stack.StackEmpty());
        cout<<endl;
    }
    void ShowAncestor(BTNode* ancestor)//输出ancestor的值及其同辈的值
                                       //孩子兄弟表示法中右子树代表兄弟
    {
        cout<<ancestor->data;
        BTNode* p=ancestor->rchild;
        while(p!=NULL)
        {
            cout<<p->data;
            p=p->rchild;
        }
    }
    void DestoryBTree(BTNode*& b)//销毁树
    {
        if(b==NULL)
            return;
        DestoryBTree(b->lchild);
        DestoryBTree(b->rchild);
        delete b;
        b=NULL;
    }
};
#endif