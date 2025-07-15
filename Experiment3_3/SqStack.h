#include <iostream>
using namespace std;
#define MAXSIZE 100 //栈最大容量

template <typename T>//顺序栈模板类
class SqStack
{//顺序栈的数据成员
    int top; //栈顶指针
    T *data; //元素存储空间
public:
    // 顺序栈的方法声明及重载编译系统默认方法声明:
    SqStack()//构造函数
    {
        data = new T[MAXSIZE]; //分配存储空间
        top = -1; //栈顶指针初始化为-1
    }
    ~SqStack()//析构函数
    {
        delete[] data; //释放存储空间
    }
    bool IsEmpty()//判断栈是否为空
    {
        return (top == -1); //栈为空则返回true
    }
    bool Push(T e)//入栈
    {
        if(top==MAXSIZE-1) //栈满则返回false
            return false;
        data[++top]=e;
        return true;
    }
    bool Pop(T &e)//出栈
    {
        if(top==-1) //栈空则返回false
        return false;
        e=data[top--];
        return true;
    }
    bool GetTop(T &e) //获取栈顶元素
    {
        if(top==-1) //栈空则返回false
        return false;
        e=data[top];
        return true;
    }
    int StackLength() //获取栈长度
    {
        return top+1;
    }
    void DispStack()
    {
        for(int i=top;i>=0;i--) //输出栈元素
        {
            cout<<data[i]<<endl;
        }
    }
};