#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <queue>
#include "SqList.h"
#include "SqStack.h"
#include "GraphInfo.h"
using namespace std;
#define Max 100
#define MAX_TERM 6    // 学期数量
#define MAX_CREDIT 10 // 每学期最大学分

struct LessonInfo{
    char id[10];
    char name[20];
    int credit;
    bool operator == (const LessonInfo& info) const{
        return strcmp(id, info.id) == 0;
    }
};

// 课程安排结构体
struct Schedule {
    vector<vector<LessonInfo>> terms; // 每个学期的课程安排
    int credit[MAX_TERM];             // 每个学期的学分
};


istream& operator>>(istream& in, VNode<LessonInfo>& info){
    in>>info.data.id>>info.data.name>>info.data.credit;
    return in;
}
ostream& operator<<(ostream& out, VNode<LessonInfo>& info){
    out<<info.data.id<<" "<<info.data.name<<" "<<info.data.credit;
    return out;
}
istream& operator>>(istream& in, ArcInfo<LessonInfo>& info){
    in>>info.From.id>>info.To.id;
    return in;
}

template<typename T>
class ALGraph
{
public:
    int vexnum;//质点数目
    int arcnum;//弧数目
    VNode<T> vertices[Max];//邻接表

public:
    ALGraph(int vnum=0, int anum=0):vexnum(vnum), arcnum(anum)
    {
        for(int i=0;i<vnum;i++)
        {
            vertices[i].firstarc = nullptr;
            vertices[i].in = 0;
        }
    }
    ~ALGraph()
    {
        for(int i=0;i<vexnum;i++)
        {
            ArcNode<T> *p = vertices[i].firstarc;
            while(p)
            {
                ArcNode<T> *q = p;
                p = p->nextarc;
                delete q;
            }
        }
    }
    void CreateGraph(int vnum, int anum, SqList<VNode<T>> data, SqList<ArcInfo<T>> arcList)
    {
        vexnum = vnum;
        arcnum = anum;
        //初始化顶点信息
        for(int i=0;i<vnum;i++)
        {
            vertices[i] = data.getElem(i);
            vertices[i].firstarc = nullptr;
        }

        //初始化弧信息
        for(int i=0;i<anum;i++)
        {
            int from = LocateVex(arcList.getElem(i).From);
            int to = LocateVex(arcList.getElem(i).To);
            if(from!= -1 && to!= -1)
            {
                ArcNode<T> *newArc = new ArcNode<T>;
                newArc->adjvex = to;
                newArc->weight = vertices[to].data.credit;
                newArc->nextarc = nullptr;
                ArcNode<T> *p = vertices[from].firstarc;
                while(p)
                {
                    p = p->nextarc;
                }
                newArc->nextarc = vertices[from].firstarc;
                vertices[from].firstarc = newArc;
            }
        }
    }

    //展示图
    void DispGraph(){
        for(int i=0;i<vexnum;i++){
            cout << "顶点" << vertices[i] << ":";
            ArcNode<T> *p = vertices[i].firstarc;
            while(p){
                cout << " -> " << vertices[p->adjvex];
                p = p->nextarc;
            }
            cout << endl;
        }
    }

    void IndegreeCal(){
        //初始化入度为0
        for(int i=0;i<vexnum;i++){
            vertices[i].in = 0;
        }
        for(int i=0;i<vexnum;i++){
            ArcNode<T> *p = vertices[i].firstarc;
            while(p){
                vertices[p->adjvex].in++;
                p = p->nextarc;
            }
        }
    }

    //拓扑排序
    bool TopOrder(Schedule &schedule,int strategy){
        IndegreeCal();//计算入度
        SqStack<int> s;
          // 初始化学期安排
        schedule.terms.resize(MAX_TERM);
        memset(schedule.credit, 0, sizeof(schedule.credit));
        for(int i=0;i<vexnum;i++){
            if(vertices[i].in == 0){
                cout << vertices[i] << "  ";
                s.Push(i);
            }
        }
        cout<<endl;
        int i=0,term = 0,termlessonlimit=vexnum/MAX_TERM+1;
        while(i<=vexnum-1){
            int index[vexnum],count=0,termlessonnum=0;
            while(!s.IsEmpty()){
                int v;
                s.GetTop(v);
                LessonInfo course = vertices[v].data; 
                if (strategy == 1 && term < MAX_TERM &&(schedule.credit[term] + course.credit > MAX_CREDIT || termlessonnum >= termlessonlimit)) {
                    break;
                }
                if(strategy == 2 && term < MAX_TERM && schedule.credit[term] + course.credit > MAX_CREDIT) {
                    break;
                }
                if (term >= MAX_TERM) {
                    cout << "课程无法在学期限制内完成！" << endl;
                    return false;
                }
                // 将课程加入学期
                s.Pop(v);
                schedule.terms[term].push_back(course);
                schedule.credit[term] += course.credit;
                //cout << vertices[v] << "  ";
                index[count++]=v;
                termlessonnum++;
                i++; 
            }
            //cout<<endl;
            term++;
            for(int j=0;j<count;j++){
                ArcNode<T> *p = vertices[index[j]].firstarc;
                while(p){
                    vertices[p->adjvex].in--;
                    if(vertices[p->adjvex].in == 0){
                        cout << vertices[p->adjvex] << "  ";
                        s.Push(p->adjvex);
                    }
                    p = p->nextarc;
                }
            }
            cout<<endl;
        }
        return true;
    }

private:
    int LocateVex(T v)
    {
        for(int i=0;i<vexnum;i++)
        {
            if(v == vertices[i].data)
                return i;
        }
        return -1;
    }
};


// 打印教学计划
void PrintPlan(Schedule &schedule, const string &filename) {
    ofstream out(filename);
    out << "教学计划：" << endl;
    for (int i = 0; i < MAX_TERM; i++) {
        out << "第 " << (i + 1) << " 学期：" << endl;
        for (auto &course : schedule.terms[i]) {
            out << course.id << " " << course.name << " (" << course.credit << " 学分)" << endl;
        }
        out << "总学分：" << schedule.credit[i] << endl << endl;
    }
    out.close();
    cout << "教学计划已保存到 " << filename << endl;
}

// 主函数
int main() {
    // 初始化课程图
    ALGraph<LessonInfo> graph;
    int vnum, anum;
    SqList<VNode<LessonInfo>> list;
    SqList<ArcInfo<LessonInfo>> list2;
    int choice;

    do {
        cout << "\n1. 输入课程信息\n";
        cout << "2. 编辑课程信息\n";
        cout << "3. 生成教学计划\n";
        cout << "4. 展示课程临接表\n";
        cout << "5. 退出程序\n";
        cout << "请输入操作选项：";
        cin >> choice;

        switch (choice) {
            case 1: {
                // 输入课程信息
                cout << "请输入课程数量和弧数量：";
                cin >> vnum >> anum;

                cout << "请输入课程信息(id name credit):\n";
                for (int i = 0; i < vnum; i++) {
                    VNode<LessonInfo> course;
                    cin >> course;
                    list.Insert(course);
                }
                cout << "请输入弧信息(起点id 终点id):\n";
                for (int i = 0; i < anum; i++) {
                    ArcInfo<LessonInfo> arc;
                    cin >> arc;
                    list2.Insert(arc);
                }
                graph.CreateGraph(vnum, anum, list, list2);
                cout << "课程信息输入完成！" << endl;
                break;
            }
            case 2: {
                // 编辑课程信息
                cout << "1. 添加课程\n2. 删除课程\n3. 修改课程信息\n4. 删除课程弧\n5. 添加课程弧\n";
                int editChoice;
                cin >> editChoice;
                if (editChoice == 1) {
                    VNode<LessonInfo> course;
                    cout << "请输入课程信息(id name credit):\n";
                    cin >> course;
                    list.Insert(course);
                    vnum=list.getLength();
                    graph.CreateGraph(vnum, anum, list, list2);
                    cout << "课程添加成功！" << endl;
                } else if (editChoice == 2) {
                    char id[10];
                    cout << "请输入要删除的课程 ID:" << endl;
                    cin >> id;
                    int index = -1;
                    for (int i = 0; i < vnum; i++) {
                        if (strcmp(id, list.getElem(i).data.id) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index != -1) {
                        list.Delete(index);
                        vnum=list.getLength();
                        graph.CreateGraph(vnum, anum, list, list2);
                        cout << "课程删除成功！" << endl;
                    } else {
                        cout << "课程不存在！" << endl;
                    }
                } else if (editChoice == 3) {
                    VNode<LessonInfo> course;
                    cout << "请输入要更新的课程信息(id name credit):\n";
                    cin >> course;
                    int index = -1;
                    for (int i = 0; i < vnum; i++) {
                        if (strcmp(course.data.id, list.getElem(i).data.id) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index != -1) {
                        list.Update(index, course);
                        graph.CreateGraph(vnum, anum, list, list2);
                        cout << "课程信息更新成功！" << endl;
                    } else {
                        cout << "课程不存在！" << endl;
                    }
                }
                else if(editChoice == 4){
                    cout<<"请输入要删除的课程弧(起点id 终点id):\n";
                    ArcInfo<LessonInfo> arc;
                    cin >> arc;
                    int index = -1;
                    for(int i=0;i<anum;i++){
                        if(list2.getElem(i).From==arc.From&&list2.getElem(i).To==arc.To){
                            index=i;
                            break;
                        }
                    }
                    if(index != -1){
                        list2.Delete(index);
                        anum=list2.getLength();
                        graph.CreateGraph(vnum, anum, list, list2);
                        cout << "课程弧删除成功！" << endl;
                    }else{
                        cout << "课程弧不存在！" << endl;
                    }
                }
                else if(editChoice == 5){
                    cout<<"请输入要添加的课程弧(起点id 终点id):\n";
                    ArcInfo<LessonInfo> arc;
                    cin >> arc;
                    list2.Insert(arc);
                    anum=list2.getLength();
                    graph.CreateGraph(vnum, anum, list, list2);
                    cout << "课程弧添加成功！" << endl;
                }
                break;
            }
            case 3: {
                // 生成教学计划
                Schedule schedule;
                int strategy;
                cout << "请选择编排策略:1. 均匀分布 2. 集中前几学期\n";
                cin >> strategy;
                if (graph.TopOrder(schedule, strategy)) {
                    string filename;
                    cout << "请输入计划保存的文件名：";
                    cin >> filename;
                    PrintPlan(schedule, filename);
                }
                break;
            }
            case 4:{
                graph.DispGraph();
                break;
            }
            case 5:
                cout << "退出程序！" << endl;
                break;
            default:
                cout << "无效选项，请重新输入！" << endl;
        }
    } while (choice != 5);

    return 0;
}