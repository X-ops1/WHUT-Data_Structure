#include <string>
#include <iostream>
#define DEFAULT_SIZE 100

using namespace std;
//循环队列类
template<typename T>
class SqQueue
{
    int front,rear;
    T *data;
public:
    SqQueue()//构造函数
    {
        data = new T[DEFAULT_SIZE];
        front = rear = 0;
    }
    ~SqQueue()//析构函数
    {
        delete[] data;
    }
    bool QueueEmpty()//判断队列是否为空
    {
        return (front==rear);
    }
    bool deQueue(T &e)//出队操作
    {
        if(front==rear)
        {
            return false;
        }
        e=data[front];
        front=(front+1)%DEFAULT_SIZE;
        return true;
    }
    bool enQueue(T e)//入队操作
    {
        if((rear+1)%DEFAULT_SIZE==front)
        {
            return false;
        }
        data[rear]=e;
        rear=(rear+1)%DEFAULT_SIZE;
        return true;
    }
    bool GetHead(T &e)//取队头操作
    {
        e=data[front];
        return true;
    }
};

//模拟患者信息结构
struct Patient
{
    int id;
    string name;

    Patient(int i=0,string name=""):id(i),name(name){}
};

//打印患者信息
void printPatient(Patient p)
{
    cout<<"患者ID: "<<p.id<<",患者姓名: "<<p.name<<endl;
}

int main()
{
    SqQueue<Patient> queue;//创建患者队列
    int choice,id=1;//模拟患者id从1开始
    Patient p;

    while(true)
    {
        cout << "医院排队系统菜单:\n";
        cout << "1. 患者挂号排队\n";
        cout << "2. 医生叫号就诊\n";
        cout << "3. 医生下班提醒\n";
        cout << "0. 退出系统\n";
        cout << "请选择操作: ";
        cin >> choice;

        if(choice==0)
            break;
        switch(choice)
        {
            case 1:
                cout<<"请输入患者姓名: ";
                cin>>p.name;
                p.id=id++;
                if(queue.enQueue(p))
                {
                    cout << p.name << "已排队等待就诊。"<<endl;
                }
                break;
            case 2:
                if(queue.deQueue(p))
                {
                    cout << "请 " << p.name << " 进入诊室。"<<endl;
                }
                else
                {
                    cout<<"当前无患者。"<<endl;
                }
                break;
            case 3:
                if(queue.QueueEmpty())
                    cout<<"没有等待的患者。"<<endl;
                else
                {
                    cout<<"医生下班，请一下患者明日再来： "<<endl;
                    while(!queue.QueueEmpty())
                    {
                        queue.deQueue(p);
                        printPatient(p);
                    }
                }
                break;
            default:
                cout<<"无效选择，请重新输入。"<<endl;
        }
    }
    cout<<"系统已退出。"<<endl;
    return 0;
}