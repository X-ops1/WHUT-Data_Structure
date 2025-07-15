#ifndef __STACK_H__
#define __STACK_H__
#include<iostream>
using namespace std;
#define MaxSize 100

template<class ElemType>
class Stack{
    private:
        typedef struct{
            ElemType* data[MaxSize];
            int top;//栈顶指针
        }SqStack;
        SqStack* s;
    public:
        Stack();
        ~Stack();
        bool Push(ElemType* e);//将元素e压入栈中
        bool Pop(ElemType* &e);//弹出栈顶元素并将其值赋给e
        bool GetTop(ElemType* &e); //获取栈顶元素的值并将其值赋给e
        bool StackEmpty();//判断栈是否为空
        int GetNum();//得到栈顶指针
        ElemType* GetElement(int suf);//得到栈中指针为suf的元素
};
template<class ElemType>
Stack<ElemType>::Stack(){
    s = new SqStack;
    s->top = -1;
    for (int i = 0; i < MaxSize; ++i) {//对 s->data 进行初始化
        s->data[i] = nullptr;
    }
}
template<class ElemType>
Stack<ElemType>::~Stack(){
    delete s;
}
template<class ElemType>
bool Stack<ElemType>::Push(ElemType* e){
    if(s->top == MaxSize-1){
        cout<<"栈满"<<endl;
        return false;
    }
    s->top++;
    s->data[s->top] = e;
    return true;
}
template<class ElemType>
bool Stack<ElemType>::Pop(ElemType* &e){
    if(s->top==-1){
        cout<<"栈空"<<endl;
        return false;
    }
    e=s->data[s->top];
    s->top--;
    return true;
}
template<class ElemType>
bool Stack<ElemType>::GetTop(ElemType* &e){
    e=s->data[s->top];
    return true;
}
template<class ElemType>
bool Stack<ElemType>::StackEmpty(){
    return (s->top==-1);
}
template<class ElemType>
int Stack<ElemType>::GetNum(){
    return s->top;
}
template<class ElemType>
ElemType* Stack<ElemType>::GetElement(int suf){
    if(suf<0||suf>s->top)
    {
        cout<<"索引无效！"<<endl;
        return nullptr;
    }
    return s->data[suf];
}

#endif //__STACK_H__