#include <iostream>
#include <fstream>
#include <cstring>
#include "hashtable.h"
using namespace std;   


int main() {
    int n;
    cout<<"请输入文件个数：";
    cin>>n;
    HashTable ht(MAXTable);
    WList* wlist;
    wlist=ht.InitializeFileIndex(n);
    for(int i=0;i<n;i++){
        char s[999];
        char ch;
        string filename = to_string(i+1) + ".txt"; // 将整数转换为字符串并拼接
        ifstream file(filename); // 打开文件
        if (!file.is_open()) {
            cerr << "无法打开文件" << endl;
            return EXIT_FAILURE;
        }
        int index=0;
        while(file.get(ch)&&ch!='#'){
            s[index++]=ch;
        }
        s[index]='\0';
        file.close();
        int word_num;
        char **word_list;
        word_list=extract_words(s,&word_num);
        for(int j=0;j<word_num;j++){
            ht.InsertAndIndex(i+1,word_list[j]);
            int pos = ht.GetAWord(word_list[j]);
            ht.FileIndex(wlist,i+1,pos);
        }
    }
    int num;
    cout<<"请输入查询个数：";
    cin>>num;
    int file[2*num];
    cout<<"请输入俩个文件编号："<<endl;
    for(int i=0;i<num;i++){
        cin>>file[2*i]>>file[2*i+1];
    }
    cout<<"俩文件相似度为："<<endl;
    for(int i=0;i<num;i++){
        cout<<ht.ComputeSim(wlist,file[2*i],file[2*i+1])<<"%"<<endl;
    }
    return 0;
}