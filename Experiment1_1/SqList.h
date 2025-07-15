#include <iostream>
#include <string>
using namespace std;

const int MAXSIZE = 100;

class Student{
public:
    string id;//学号
    string name;//姓名
    double gpa;//绩点

    // 默认构造函数
    Student() : id(""), name(""), gpa(0.0) {}

    // 带参数构造函数
    Student(string id, string name, double gpa)
    {
        this->id = id;
        this->name = name;
        this->gpa = gpa;
    }

    bool operator==(const Student& s) const{ //重载运算符，自定义比较逻辑
        return this->id == s.id; //这个重载的 == 运算符在 SqList 类的 LocateElem 函数中被用来查找具有相同学号的 Student 对象
    }

    void display() const { // 显示学生信息
        cout << "学号: " << id << ", 姓名: " << name << ", 绩点: " << gpa << endl;
    }
};

template <typename T>
class SqList
{// 顺序表的数据成员
    int length; // 顺序表的当前长度
    T *data; // 元素存储空间的首地址
public:// 顺序表的函数成员
    SqList() // 构造一个空表
    {
        data = new T[MAXSIZE]; // 为顺序表分配存储空间
        length = 0; // 顺序表的长度为 0
    }
    ~SqList() // 析构函数
    {
        delete[] data; // 释放存储空间
    }
    void clear() // 清空顺序表
    {
        for (int i = 0; i < length; i++) {
            data[i] = T();  // 将每个元素重置为其默认值
        }
        length = 0;  // 设置顺序表的长度为 0
    }
    void CreateList(T v[], int n) // 根据数组 v 的内容构造顺序表
    {
        length = n;
        data = new T[n+1]; // 为顺序表分配存储空间
        for(int i = 1; i <= n; i++) // 逐个元素赋值
        {
            data[i] = v[i-1];
        }
        cout << "顺序表已创建！" << endl;
    }
    int ListLength() // 取顺序表长度
    {
        return length;
    }
    int LocateElem(T e) // 元素定位，求指定元素在顺序表中的位置
    {
        for(int i = 1; i <= length; i++)
        {
            if(data[i] == e)
            {
                return i;
            } 
        }
        return 0;
    }
    bool GetElem(int i, T &e) // 取顺序表中第 i 个元素的值
    {
        if(i < 1 || i > length) // 越界检查
        {
            cout << "越界！" << endl;
            return false;
        }
        e = data[i];
        return true;
    }
    bool SetElem(int i, const T &e) // 修改顺序表中第 i 个元素的值
    {
        if(i < 1 || i > length) // 越界检查
        {
            cout << "越界！" << endl;
            return false;
        }
        data[i] = e;
        return true;
    }
    bool ListDelete(int i, T &e) // 删除顺序表中第 i 个元素
    {
        if(i < 1 || i > length) // 越界检查
        {
            cout << "越界！" << endl;
            return false;
        }
        e = data[i];
        for(int j = i;j<length;j++)
        {
            data[j]=data[j+1];
        }
        length--;
        return true;
    }
    bool ListInsert(int i, T e) // 在顺序表第 i 个位置插入元素
    {
        if (i < 1 || i > length + 1 || length >= MAXSIZE) { // 添加检查顺序表是否已满
        cout << "插入失败：越界或顺序表已满！" << endl;
        return false;
        }      
        for(int j = length;j>=i;j--)
        {
            data[j+1] = data[j];
        }
        data[i] = e;
        length++;
        return true;
    }
    void DispList() // 输出顺序表内容
    {
        for(int i = 1;i<=length;i++)
        {
            data[i].display(); // 输出学生信息
        }
        cout << endl;
    }
};
