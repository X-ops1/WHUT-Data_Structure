#include <iostream>
#include "Node.h"

using namespace std;

class StudentInfoSystem 
{
    LinkList<Student> studentList;//学生信息表
public:
    void Display()//显示当前所有学生信息记录
    {
        cout<<"当前所有学生信息记录如下："<<endl;
        studentList.DispList();
    }

    void Input(int i=1)//从键盘输入一条学生信息记录，插入到表中指定的位置；
    {
        Student stu;
        cout << "请输入学号：";
        cin >> stu.id;
        if (stu.id.empty()) {
        cout << "学号不能为空！" << endl;
        return;
        }
        cout << "请输入姓名：";
        cin >> stu.name;
        if (stu.name.empty()) {
        cout << "姓名不能为空！" << endl;
        return;
        }
        cout << "请输入绩点：";
        cin >> stu.gpa;
        if (stu.gpa < 0.0 || stu.gpa > 5.0) {
        cout << "绩点无效，必须在 0.0 到 5.0 之间！" << endl;
        return;
        }
        if(i==0)
        {
            if(!studentList.ListInsert(1,stu))
            {
            cout<<"插入失败！"<<endl;
            }
            else
            {
            cout<<"插入成功！"<<endl;   
            }
        }
        else
        {
            int pos;
            cout<<"请输入插入位置(从1开始):";
            cin>>pos;
            if(!studentList.ListInsert(pos,stu))
            {
                cout<<"插入失败！"<<endl;
            }
            else
            {
                cout<<"插入成功！"<<endl;   
            }
        }
    }

    void Search() //根据学号或者记录的位置查找学生的各项信息；
    {
        cout<<"请输入查找方式(1:学号 2:位置):";
        int choice;
        cin>>choice;
        Student stu;
        if(choice==1)
        {
            cout<<"请输入学号：";
            cin>>stu.id;
            int pos=studentList.LocateElem(stu);
            if(pos)
            {
                cout<<"找到学生："<<endl;
                studentList.GetElem(pos,stu);
                cout << "学号：" << stu.id << ", 姓名：" << stu.name << ", 绩点：" << stu.gpa << endl;
            }
            else
            {
                cout<<"未找到该学生！"<<endl;
            }
        }
        else if(choice==2)
        {
            cout<<"请输入位置：";
            int pos;
            cin>>pos;
            if(studentList.GetElem(pos,stu))
            {
                cout<<"找到学生："<<endl;
                cout << "学号：" << stu.id << ", 姓名：" << stu.name << ", 绩点：" << stu.gpa << endl;
            }
            else
            {
                cout<<"未找到该学生！"<<endl;
            }
        }
        else
        {
            cout<<"无效选择！"<<endl;
        }
    }

    bool Delete() //删除指定位置的学生信息记录；
    {
        int pos;
        cout<<"请输入你要删除的学生的位置："<<endl;
        cin>>pos;
        Student stu;
        if(studentList.ListDelete(pos,stu))
        {
            cout<<"删除成功！"<<endl;
            return true;
        }
        else
        {
            cout<<"删除失败！"<<endl;
            return false;
        }
    }

    void Update() //更新指定位置的学生信息记录；
    {
        int pos;
        cout<<"请输入你要更新的学生的位置："<<endl;
        cin>>pos;
        Student stu;
        cout << "请输入学号：";
        cin >> stu.id;
        if (stu.id.empty()) {
        cout << "学号不能为空！" << endl;
        return;
        }
        cout << "请输入姓名：";
        cin >> stu.name;
        if (stu.name.empty()) {
        cout << "姓名不能为空！" << endl;
        return;
        }
        cout << "请输入绩点：";
        cin >> stu.gpa;
        if (stu.gpa < 0.0 || stu.gpa > 5.0) {
        cout << "绩点无效，必须在 0.0 到 5.0 之间！" << endl;
        return;
        }
        if(studentList.SetElem(pos,stu))
        {
            cout<<"更新成功！"<<endl;
        }
        else
        {
            cout<<"更新失败！"<<endl;
        }
    }

    void Count() //统计表中学生人数:
    {
        cout<<"当前学生人数为："<<studentList.ListLength()<<endl;
    }

    void Sort() //按照学号或者绩点进行排序
    {
        cout<<"请输入排序方式(1:学号 2:绩点):";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            cout<<"按照学号排序"<<endl;
            for(int i=1;i<studentList.ListLength();i++)
            {
                for(int j=1;j<studentList.ListLength()-i+1;j++)
                {
                    Student stu1,stu2;
                    studentList.GetElem(j,stu1);
                    studentList.GetElem(j+1,stu2);
                    if(stu1.id>stu2.id)
                    {
                        swap(stu1,stu2);
                        studentList.SetElem(j,stu1);
                        studentList.SetElem(j+1,stu2);
                    }
                }
            }
            cout<<"按学号排序完成！"<<endl;
        }
        else if(choice==2)
        {
            cout<<"按照绩点排序"<<endl;
            for(int i=1;i<studentList.ListLength();i++)
            {
                for(int j=1;j<studentList.ListLength()-i+1;j++)
                {
                    Student stu1,stu2;
                    studentList.GetElem(j,stu1);
                    studentList.GetElem(j+1,stu2);
                    if(stu1.gpa<stu2.gpa)
                    {
                        swap(stu1,stu2);
                        studentList.SetElem(j,stu1);
                        studentList.SetElem(j+1,stu2);
                    }
                }
            }
            cout<<"按绩点排序完成！"<<endl;
        }
        else
        {
            cout<<"无效选择！"<<endl;
        }
    }

    void Clear() //清空表中所有记录
    {
        studentList.clear();
        cout<<"清空成功！"<<endl;
    }
};

int main()
{
    StudentInfoSystem system;
    int choice;
    int k=0;
    int flag=1;
    cout << "欢迎使用学生信息管理系统！" << endl;
    while(flag)
    {
        cout << "1. 显示所有学生信息" << endl;
        cout << "2. 录入学生信息" << endl;
        cout << "3. 查找学生信息" << endl;  
        cout << "4. 删除学生信息" << endl;
        cout << "5. 更新学生信息" << endl;
        cout << "6. 统计学生人数" << endl;
        cout << "7. 按学号或者绩点排序" << endl;
        cout << "8. 清空所有记录" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请输入你的选择：";
        cin >> choice;
        switch (choice) {
            case 1:
                system.Display();
                break;
            case 2:
            {
                if(k==0)
                {
                    system.Input(0);
                    system.Display();
                }
                else
                {
                    system.Input();
                    system.Display();
                }
                k++;
                break;
            }
            case 3:
                system.Search();
                break;
            case 4:
                if(system.Delete())
                {
                system.Display();
                }
                break;
            case 5:
                system.Update();
                system.Display();
                break;
            case 6:
                system.Count();
                break;
            case 7:
                system.Sort();
                system.Display();
                break;
            case 8:
                system.Clear();
                break;
            case 0:
                flag=0;
                break;
            default:
                cout << "无效选择，请重新输入。" << endl;
        }
        cout << endl;
    }
    return 0;
}