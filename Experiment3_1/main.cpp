#include <iostream>
#include "BTree.h"
#include "Stack.h"

using namespace std;

int main()
{
    cout<<"请以括号表示法输出二叉树结构：";
    string str;
    char ch;
    cin>>str;
    BTree<char> tree(str);
    cout<<"后序遍历递归算法输出：";
    tree.PostOrder(tree.GetRoot());
    cout<<endl;
    cout<<"前序遍历非递归算法输出：";
    tree.PreOrderRe(tree.GetRoot());
    cout<<endl;
    cout<<"请输入指定人物代号，以查询其所有长辈：";
    cin>>ch;
    cout<<ch<<"的所有长辈为：";
    tree.FindAllAncestor(ch);
    return 0;
}