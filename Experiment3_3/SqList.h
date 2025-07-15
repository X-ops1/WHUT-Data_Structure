#include <iostream>
#define MAX 10000
using namespace std;

template <class T>
class SqList {
private:
    T *elem; // 用于存储元素的数组
    int length; // 当前元素的数量
    int listsize; // 数组的最大容量

public:
    // 构造函数
    SqList(int size = MAX) : listsize(size), length(0) {
        elem = new T[listsize];
    }

    // 析构函数
    ~SqList() {
    }
    int getLength(){
        return length;
    }
    T getElem(int i){
        return elem[i];
    }
    // 输入线性表
    void InputList() {
        cout << "请输入元素个数: ";
        int n;
        cin >> n;
        length = n;
        cout << "请输入元素: ";
        for (int i = 0; i < n; ++i) {
            cin >> elem[i];
        }
    }
    // 输出线性表
    void OutputList() {
        for (int i = 0; i < length; ++i) {
            cout << elem[i];
        }
    }

    // 在位置 i 插入一个元素 e
    bool Insert(int i, T e) {
        if (i < 0 || i > length) return false;
        if (length >= listsize) return false;
        for (int j = length; j > i; --j) {
            elem[j] = elem[j - 1];
        }
        elem[i] = e;
        ++length;
        return true;
    }

    // 在末尾插入一个元素 e
    bool Insert(T e) {
        if (length >= listsize) return false;
        elem[length] = e;
        ++length;
        return true;
    }

    // 删除位置 i 的元素
    bool Delete(int i, T &e) {
        if (i < 0 || i >= length) return false;
        e = elem[i];
        for (int j = i; j < length - 1; ++j) {
            elem[j] = elem[j + 1];
        }
        --length;
        return true;
    }

    // 删除位置 i 的元素
    bool Delete(int i) {
        if (i < 0 || i >= length) return false;
        for (int j = i; j < length - 1; ++j) {
            elem[j] = elem[j + 1];
        }
        --length;
        return true;
    }


    // 删除位置 i 的元素
    bool DeleteByIndex(int i) {
        if (i < 0 || i >= length) return false;
        for (int j = i; j < length - 1; ++j) {
            elem[j] = elem[j + 1];
        }
        --length;
        return true;
    }


    // 在位置 i 更新一个元素 e
    bool Update(int i, T e) {
        if (i < 0 || i >= length) return false;
        elem[i] = e;
        return true;
    }

    // 根据元素 e 查找在线性表中的位置
    int Locate(T e) {
        for (int i = 0; i < length; ++i) {
            if (elem[i] == e) return i;
        }
        return -1; // 未找到 
    }
};
