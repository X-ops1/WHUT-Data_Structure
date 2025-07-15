#include <iostream>
#include <string>
using namespace std;

class Student{
public:
    string id;//学号
    string name;//姓名
    double gpa;//绩点

    // 默认构造函数
    Student() : id(""), name(""), gpa(0.0) {}

    // 带参数构造函数
    Student(string id, string name, double gpa):id(id),name(name),gpa(gpa){};

    bool operator==(const Student& s) const{ //重载运算符，自定义比较逻辑
        return this->id == s.id; //这个重载的 == 运算符在 SqList 类的 LocateElem 函数中被用来查找具有相同学号的 Student 对象
    }

    void display() const { // 显示学生信息
        cout << "学号: " << id << ", 姓名: " << name << ", 绩点: " << gpa << endl;
    }
};

template <typename T>
//结点类
class Node 
{   
    public:
    //数据成员
    T data;//数据域
    Node<T> *next;//指针域
    //构造函数
    Node():next(NULL){};//无参数的构造函数
    Node(T e,Node<T> *next=NULL):data(e),next(next){};//已知数数据元素值和指针建立结点
};

// 单链表类
template <typename T>
class LinkList
{
    // 单链表的数据成员
    Node<T> *head; // 头结点指针
    int length; // 单链表长度
    public:
    // 单链表的函数成员
    LinkList() // 无参数的构造函数
    {
        head = new Node<T>();
        length = 0;
    }

    ~LinkList() // 析构函数
    {
        Node<T> *p=head,*q;
        while(p)
        {
            q=p->next;
            delete p;
            p=q;
        }
        head=NULL;
        length=0;
    }

    void CreateList(T v[], int n) // 根据数组 v 的内容构造顺序表
    {
        head = new Node<T>();
        head->next=NULL;
        Node<T> *tail=head;
        for(int i=0;i<n;i++)
        {
            tail->next=new Node<T>(v[i]);
            tail=tail->next;
        }
        length=n;
    }

    int ListLength() // 取顺序表长度
    {
        return length;
    }

    int LocateElem(T e)  // 元素定位，求指定元素在顺序表中的位置
    {
        Node<T> *p=head->next;
        int j=1;
        while(p)
        {
            if(p->data==e)
            {
                return j;
            }
            else
            {
                j++;
                p=p->next;
            }
        }
        return 0;//返回0表示没有找到
    }

    bool GetElem(int i, T &e)  // 取顺序表中第 i 个元素的值
    {
        if(i<1 || i> length)
        {
            cout << "越界！" << endl;
            return false;
        }
        Node<T> *p=head->next;
        for(int j=1;j<i;j++)
        {
            if (p == nullptr) // 检查是否到达链表末尾
            {
            return false;
            }
            p=p->next;
        }
        e=p->data;
        return true;
    }

    bool SetElem(int i, const T &e) // 修改顺序表中第 i 个元素的值
    {
        Node<T> *p=head->next;
        if(i<1 || i> length)
        {
            cout << "越界！" << endl;
            return false;
        }
        for(int j=1;j<i;j++)
        {
            if (p == nullptr) // 检查是否到达链表末尾
            {
            return false;
            }
            p=p->next;
        }
        p->data=e;
        return true;
    }

    bool ListDelete(int i, T &e) // 删除顺序表中第 i 个元素
    {
        Node<T> *p=head->next,*pre=head;
        if(i<1 || i> length)
        {
            cout << "越界！" << endl;
            return false;
        }
        for(int j=1;j<i;j++)
        {
            if (p == nullptr) // 检查是否到达链表末尾
            {
            return false;
            }
            pre=pre->next;
            p=p->next;
        }
        e=p->data;
        pre->next=p->next;
        delete p;
        length--;
        return true;
    }

    bool ListInsert(int i, T e) // 在顺序表第 i 个位置插入元素
    {
        Node<T> *pre=head;
        if(i<1 || i> length + 1)
        {
            cout << "越界！" << endl;
            return false;
        }
        for(int j=1;j<i;j++)
        {
            pre=pre->next;
        }
        Node<T> *s=new Node<T>(e);
        s->next=pre->next;
        pre->next=s;
        length++;
        return true;
    }

    void DispList()
    {
        Node<T> *p = head->next;
        while (p) 
        {
            p->data.display();
            p = p->next;
        }
    }

    void clear()
    {
        Node<T> *p = head->next;
        while (p) {
        Node<T> *q = p;
        p = p->next;
        delete q;
        }
        // 保留头节点并将其 next 置为 nullptr
        head->next = nullptr;
        length = 0;
    }
};