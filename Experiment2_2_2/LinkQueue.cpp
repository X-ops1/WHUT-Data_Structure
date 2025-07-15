#include <string>
#include <iostream>

using namespace std;

// 先声明 LinkQueue
template <typename T>
class LinkQueue; // 前向声明

//节点类
template <typename T>
class Node
{
    friend class LinkQueue<T>;
    //数据成员
    T data;
    Node<T> *next;
    public:
    //构造函数
    Node():next(NULL){};//无参数的构造函数
    Node(T item,Node<T> *next=NULL):data(item),next(next){};//已知数数据元素值和指针建立结构
};


//链式队列类
template <typename T>
class LinkQueue
{
     //数据成员
    Node<T> *front;//指向队首结点
    Node<T> *rear;//指向队尾结点
    public:
        LinkQueue()//构造函数
        {
            front=new Node<T>();
            rear=front;
            front->next=NULL;
        }
        ~LinkQueue()//析构函数
        {
            while(front)
            {
                rear=front->next;
                free(front);
                front=rear;
            }
        }
        bool QueueEmpty()//判断队列是否为空
        {
            return (front==rear);
        }
        bool deQueue(T &e)//出队操作
        {
            if(front==rear)
                return false;
            Node<T> *p=front->next;
            e=p->data;
            front->next=p->next;
            if(rear==p)//队列中只有一个结点时
            {
                rear=front;
            }
            free(p);
            return true;
        }
        bool enQueue(T e)//入队操作
        {
            Node<T> *p;
            p=new Node<T>();
            p->data=e;
            p->next=NULL;
            rear->next=p;
            rear=p;
            return true;
        }
        bool GetHead(T &e)//取队头操作
        {
            e=front->next->data;
            return true;
        }
};

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
    LinkQueue<Patient> queue;//创建患者队列
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