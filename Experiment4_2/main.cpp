#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Student类定义
class Student {
private:
    string _name;   // 姓名
    int _number;    // 学号
    int _chinese;   // 语文成绩
    int _math;      // 数学成绩
    int _english;   // 英语成绩
    int _sum;       // 总分

public:
    // 构造函数
    Student() : _name(""), _number(0), _chinese(0), _math(0), _english(0), _sum(0) {}
    // 设置学生信息
    void putMessage(string name, int number, int chinese, int math, int english) {
        _name = name;
        _number = number;
        _chinese = chinese;
        _math = math;
        _english = english;
        _sum = chinese + math + english;
    }
    // 打印学生信息
    void printStudent() const {
        cout << _name << " " << _number << " " << _sum << endl;
    }
    int stu_chinese() const {
        return _chinese;
    }
    int stu_english() const {
        return _english;
    }
    string stu_name() const {
        return _name;
    }
    int stu_sum() const {
        return _sum;
    }
    int stu_math() const {
        return _math;
    }
    int stu_number() const {
        return _number;
    }
    void operator=(const Student& s){
        _name = s._name;
        _number = s._number;
        _chinese = s._chinese;
        _math = s._math;
        _english = s._english;
        _sum = s._sum;
    }
    bool operator<(const Student& s) const{
        if(_sum<s._sum)
            return true;
        else if(_sum==s._sum){
            if(_math<s._math){
                return true;
            }
            else if(_math==s._math){
                if(_number<s._number)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
};

// 分区函数
int partition(Student arr[], int low, int high) {
    // 选择最右边的元素作为基准值
    Student pivot = arr[high];
    int i = low - 1;  // 小于基准值的元素的索引
    
    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于基准值
        if (arr[j] < pivot) {
            i++;  // 增加小于基准值元素的索引
            // 交换arr[i]和arr[j]
            Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 最后将基准值放到正确的位置
    Student temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // 返回基准值的索引
    return i + 1;
}

// 快速排序主函数
void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        // partition函数返回基准值的下标
        int pi = partition(arr, low, high);
        
        // 分别对基准值左右两部分递归排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main() {
    int n;
    cout<<"输入参加评选的学生人数。"<<endl;
    cin>>n;
    Student stu[n];
    cout<<"输入学生信息。(姓名 学号 语文 数学 英语)"<<endl;
    for(int i=0;i<n;i++){
        string name;
        int number, chinese, math, english; 
        cin>>name>>number>>chinese>>math>>english;
        stu[i].putMessage(name, number, chinese, math, english);
    }
    quickSort(stu, 0, n-1);
    cout<<"前5名:"<<endl;
    for(int i=n-1;i>n-6;i--){
        stu[i].printStudent();
    }
    return 0;
}
