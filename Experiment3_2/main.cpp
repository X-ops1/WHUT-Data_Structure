#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
#define numMAX 20
#define MAX 10000
#define INF 99999
#include "SqList.h"

//质点信息
struct Vex{
    string Code;
    string Name;
    bool operator==(const Vex& svex) const{
        return Code==svex.Code;
    }
    friend istream& operator>>(istream& in,Vex& svex){
        cout<<"请输入点的编号和名称：";
        in>>svex.Code>>svex.Name;
        return in;
    }
    friend ostream& operator<<(ostream& out,Vex& svex){
        out<<"编号："<<svex.Code<<" 名称："<<svex.Name<<endl;
        return out;
    }
};

//边的信息
struct Edge{
    Vex vex1;
    Vex vex2;
    int weight;
    bool operator==(const Edge& sedge) const{
        return (vex1 == sedge.vex1 && vex2 == sedge.vex2 && weight == sedge.weight);
    }
    friend istream& operator>>(istream& in,Edge& sedge){
        cout<<"请输入边的俩点编号和权值：";
        in>>sedge.vex1.Code>>sedge.vex2.Code>>sedge.weight;
        return in;
    }
    friend ostream& operator<<(ostream& out,Edge& sedge){
        out<<"点1编号:"<<sedge.vex1.Code<<" 点2编号:"<<sedge.vex2.Code<<" 权值为："<<sedge.weight<<endl;
        return out;
    }
};

class Graph{
    private:
        int AdjMatrix[numMAX][numMAX];//邻接矩阵
        SqList<Vex> Vexs;//点的集合
        SqList<Edge> Edges;//边的集合
        int VexNum;//点的个数
    public:
        Graph():VexNum(0){
            for (int i = 0; i < numMAX; ++i) 
            {
                for (int j = 0; j < numMAX; ++j)
                {
                    AdjMatrix[i][j] = INF;
                }
            }
        };
        ~Graph(){};
        void display()
        {
            cout<<"点的编号和名称："<<endl;
            Vexs.OutputList();
            cout<<"边的俩点编号和权值："<<endl;
            Edges.OutputList();
            cout<<"邻接矩阵为："<<endl;
            for(int i=0;i<VexNum;i++)
            {
                for(int j=0;j<VexNum;j++)
                {
                    cout << left << setw(5) << AdjMatrix[i][j] << " "; // 设置左对齐和字段宽度
                }
                cout<<endl;
            }
        }
        bool InsertVex(Vex svex)
        {
            if (VexNum >= numMAX) {
                cout << "点的个数超过最大值" << endl;
                return false;
            }
            Vexs.Insert(Vexs.getLength(), svex);
            VexNum++;
            return true;
        }
        bool DeleteVex(Vex svex)
        {
            Vex temp;
            for (int i = 0; i < Vexs.getLength();i++) 
            {
                if (Vexs.getElem(i).Code == svex.Code) 
                {
                    Vexs.Delete(i,temp);
                    VexNum--;
                    // 更新邻接矩阵
                    for (int j = i; j < VexNum; ++j) {
                        for(int k = 0; k < VexNum; k++){
                            AdjMatrix[j][k] = AdjMatrix[j+1][k];
                        }
                    }
                    return true;
                }
            }
            return false;
        }
        bool UpdateVex(Vex svex)
        {
            Vex temp;
            for (int i = 0; i < Vexs.getLength();i++) 
            {
                if (Vexs.getElem(i).Code == svex.Code) 
                {
                    Vexs.Update(i,svex);
                    return true;
                }
            }
            return false;
        }
        bool InsertEdge(Edge sedge)
        {
            if(Vexs.Locate(sedge.vex1)>=0&&Vexs.Locate(sedge.vex2)>=0)
            {
                if(Edges.Insert(Edges.getLength(), sedge))
                {
                    // 更新邻接矩阵
                    AdjMatrix[Vexs.Locate(sedge.vex1)][Vexs.Locate(sedge.vex2)] = sedge.weight;
                    AdjMatrix[Vexs.Locate(sedge.vex2)][Vexs.Locate(sedge.vex1)] = sedge.weight;
                    return true;
                }
            }
            return false;
        }
        bool DeleteEdge(Edge sedge)
        {
            if(Vexs.Locate(sedge.vex1)>=0&&Vexs.Locate(sedge.vex2)>=0)
            {
                Edge temp;
                if(Edges.Delete(Edges.Locate(sedge),temp))
                {
                    AdjMatrix[Vexs.Locate(sedge.vex1)][Vexs.Locate(sedge.vex2)] = 0;
                    AdjMatrix[Vexs.Locate(sedge.vex2)][Vexs.Locate(sedge.vex1)] = 0;
                    return true;
                }
            }
            return false;
        }
        bool UpdateEdge(Edge sedge)
        {
            if(Vexs.Locate(sedge.vex1)>=0&&Vexs.Locate(sedge.vex2)>=0)
            {
                int k = Edges.Locate(sedge);
                if(Edges.Update(k, sedge))
                {
                    // 更新邻接矩阵
                    AdjMatrix[Vexs.Locate(sedge.vex1)][Vexs.Locate(sedge.vex2)] = sedge.weight;
                    AdjMatrix[Vexs.Locate(sedge.vex2)][Vexs.Locate(sedge.vex1)] = sedge.weight;
                    return true;
                }
            }
            return false;
        }
        Edge GetEdge(string vex1Code,string vex2Code)
        {
            Edge temp;
            int v1,v2;
            for (int i = 0; i < Vexs.getLength();i++) 
            {
                if (Vexs.getElem(i).Code == vex1Code) 
                {
                    v1=i;
                }
                if (Vexs.getElem(i).Code == vex2Code) 
                {
                    v2=i;
                }
            }
            temp.vex1=Vexs.getElem(v1);
            temp.vex2=Vexs.getElem(v2);
            temp.weight=AdjMatrix[v1][v2];
            return temp;
        }
        Vex GetVex(string vex1Code)
        {
            Vex temp;
            for (int i = 0; i < Vexs.getLength();i++) 
            {
                if (Vexs.getElem(i).Code == vex1Code) 
                {
                    temp=Vexs.getElem(i);
                }
            }
            return temp;
        }
        void SetVexNum(int num)
        {
            VexNum=num;
        }

        void PrimMinTree()
        {
            int lowcost[VexNum];//候选最短边的权值
            int closest[VexNum];//候选最短边的邻接点
            int mincost,k;
            for(int i=0;i<VexNum;i++)
            {
                lowcost[i]=AdjMatrix[0][i];
                closest[i]=0;
            }
            lowcost[0]=0;
            cout<<"Prim算法构建通信网:"<<endl;
            for(int i=1;i<VexNum;i++)
            {  //输出n-1条边
                mincost=INF;
                for(int j=0;j<VexNum;j++)
                {  //找出最近的顶点
                    if(lowcost[j]!=0&&lowcost[j]<mincost){
                        mincost=lowcost[j];
                        k=j;
                    }
                }
                cout<<"边("<<Vexs.getElem(closest[k]).Code<<","<<Vexs.getElem(k).Code<<")权为:"<<mincost<<endl;
                lowcost[k]=0;
                for(int j=0;j<VexNum;j++)
                {
                    if(lowcost[j]!=0&&AdjMatrix[k][j]<lowcost[j])
                    {
                        lowcost[j]=AdjMatrix[k][j];
                        closest[j]=k;
                    }
                }
            }
        }

        void KruskalMinTree()
        {
            Edge aPath[numMAX*(numMAX-1)/2];
            for(int i=0;i<Edges.getLength();i++)
            {
                aPath[i]=Edges.getElem(i);
            }
            for(int i=0;i<Edges.getLength();i++)
            {
                for(int j=i+1;j<Edges.getLength();j++)
                {
                    if(aPath[i].weight>aPath[j].weight)
                    {
                        Edge temp=aPath[i];
                        aPath[i]=aPath[j];
                        aPath[j]=temp;
                    }
                }
            }
            cout<<"Kruskal算法构建通信网:"<<endl;
            int VexSet[numMAX];
            int v1,v2,vs1,vs2;
            for(int i=0;i<Vexs.getLength();i++)
            {
                VexSet[i]=i;
            }
            for(int i=0;i<Edges.getLength();i++)
            {
                v1 = Vexs.Locate(aPath[i].vex1);
                v2 = Vexs.Locate(aPath[i].vex2);
                vs1 = VexSet[v1];
                vs2 = VexSet[v2];
                if(vs1!=vs2)
                {
                    cout<<"边("<<aPath[i].vex1.Code<<","<<aPath[i].vex2.Code<<")权为:"<<aPath[i].weight<<endl;
                    for(int j=0;j<numMAX;j++)//合并俩个连通分量
                    {
                        if(VexSet[j]==vs2)
                        {
                            VexSet[j]=vs1;
                        }
                    }
                }
            }
        }
};

int main(){
    Graph G;
    while(true){
        int choice;
        cout<<"1.插入点 2.删除点 3.更新点 4.插入边 5.删除边 6.更新边 7.获取边 8.获取点 9.输出图 10.Prim算法构建通信网 11.Kruskal算法构建通信网 0.退出"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
            {
                Vex svex;
                cin>>svex;
                G.InsertVex(svex);
                break;
            }
            case 2:
            {
                Vex svex;
                cin>>svex;
                G.DeleteVex(svex);
                break;
            }
            case 3:
            {
                Vex svex;
                cin>>svex;
                G.UpdateVex(svex);
                break;
            }
            case 4:
            {
                Edge sedge;
                cin>>sedge;
                G.InsertEdge(sedge);
                break;
            }
            case 5:
            {
                Edge sedge;
                cin>>sedge;
                G.DeleteEdge(sedge);
                break;
            }
            case 6:
            {
                Edge sedge;
                cin>>sedge;
                G.UpdateEdge(sedge);
                break;
            }
            case 7:
            {
                cout<<"请输入边的俩点编号：";
                string vex1Code,vex2Code;
                cin>>vex1Code>>vex2Code;
                Edge sedge=G.GetEdge(vex1Code,vex2Code);
                cout<<sedge<<endl;
                break;
            }
            case 8:
            {
                cout<<"请输入点的编号：";
                string vex1Code;
                cin>>vex1Code;
                Vex svex=G.GetVex(vex1Code);
                cout<<svex<<endl;
                break;
            }
            case 9:
            {
                G.display();
                break;
            }
            case 10:
            {
                G.PrimMinTree();
                break;
            }
            case 11:
            {
                G.KruskalMinTree();
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                cout<<"输入错误"<<endl;
                continue;
            }
        }
    }
    return 0;
}