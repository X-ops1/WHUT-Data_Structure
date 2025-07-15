#include <iostream>
#include <cstring>
using namespace std;
#define MAXS 10   //最大字符串长度
#define MINS 3    //最小字符串长度
#define MAXB 5    //每个字符占得位数
#define MAXTable 100  //散列表规模

typedef struct FileEntry {
    int Words;        //文件的词汇索引表
    struct FileEntry* Next;
} WList;

/*--------------------------简化版散列列表定义及初始化--------------------------*/

typedef struct WordEntry {
    short FileNo;
    struct WordEntry* Next;
} FList;

typedef char ElementType[MAXS + 1];

typedef struct HashEntry {
    short FileNo;     //为0是结点为空
    FList* InvIndex;  //倒排索引
    ElementType Element;
} HashEntry;

// 辅助函数：将字符串转换为小写
void to_lower_case(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// 主函数：提取并返回符合条件的单词
char** extract_words(char* input, int* word_count) {
    // 初始化
    char** words = (char**)malloc(MAXTable * sizeof(char*)); // 预留空间，最多100个单词
    if (!words) return NULL;

    int word_index = 0;  // 用来计数单词个数
    char word_buffer[MAXS + 1]; // 单词最多10个字母，+1为了结束符'\0'
    int char_index = 0;

    *word_count = 0;

    // 遍历输入字符串
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) { // 字母字符
            // 记录字母到缓存
            if (char_index < MAXS) {  // 保证不超过10个字母
                word_buffer[char_index++] = input[i];
            }
        } else {  // 非字母字符，意味着一个单词结束
            if (char_index >= 3) {  // 长度必须大于等于3
                word_buffer[char_index] = '\0';  // 字符串结束
                // 分配内存并存储单词（小写形式）
                words[word_index] = (char*)malloc((char_index + 1) * sizeof(char));
                if (words[word_index]) {
                    strcpy(words[word_index], word_buffer);
                    to_lower_case(words[word_index]); // 转换为小写
                    word_index++;
                    (*word_count)++;
                }
            }
            char_index = 0;  // 重置缓存
        }
    }

    // 处理最后一个单词（如果存在）
    if (char_index >= 3) {
        word_buffer[char_index] = '\0';
        words[word_index] = (char*)malloc((char_index + 1) * sizeof(char));
        if (words[word_index]) {
            strcpy(words[word_index], word_buffer);
            to_lower_case(words[word_index]);
            word_index++;
            (*word_count)++;
        }
    }

    return words;
}

class HashTable {
private:


public:
    int TableSize;
    HashEntry* TheCells;
    HashTable(int TableSize)  //构造函数
    {
        InitializeTable(TableSize);
    }
    ~HashTable()  //析构函数
    {
        delete[] TheCells;
    }
    void InitializeTable(int Size)  //创建散列表
    {
        TableSize = Size;
        TheCells = new HashEntry[TableSize];
        for (int i = 0; i < TableSize; ++i) {
            TheCells[i].FileNo = 0; // 表示结点为空
            TheCells[i].InvIndex = NULL; 
            strcpy(TheCells[i].Element, "");
        }
    }
    static WList* InitializeFileIndex(int Size)      //初始化文件的词汇索引表
    {
        WList* FileIndex = new WList[Size];
        for (int i = 0; i < Size; ++i) {
            FileIndex[i].Words = 0;
            FileIndex[i].Next = NULL;
        }
        return FileIndex;
    }
    int GetAWord(ElementType Word)            //从当前字符开始读到单词尾的第一个非字母符号为止
    {
        for(int i=0;i<TableSize;i++){
            if(TheCells[i].FileNo!=0 && strcmp(TheCells[i].Element,Word)==0){
                return i;
            }
        }
        return -1;
    }
    static int Hash(char* Key, int P)               //字符串key移位法散列函数
    {
        unsigned int h = 0;
        while (*Key != '\0')
            h = (h << MAXB) + (*Key++ - 'a');
        return h % P;
    }
    int Find(ElementType Key)   //返回key的位置，或是适合插入key的位置
    {
        int pos = Hash(Key, TableSize);
        while (TheCells[pos].FileNo != 0 && strcmp(TheCells[pos].Element, Key) != 0) {
            pos = (pos + 1) % TableSize;
        }
        return pos;
    }
    int InsertAndIndex(int FileNo, ElementType Key)  //将key插入散列表，同时插入倒排索引表
    {
        FList *F;
        int pos = Find(Key);  // 找位置

        if (TheCells[pos].FileNo != FileNo) {  // 插入散列表
            if (!TheCells[pos].FileNo)  // 新单词
                strcpy(TheCells[pos].Element, Key);
            TheCells[pos].FileNo = FileNo;  // 最近更新
            F = (WordEntry*)malloc(sizeof(struct WordEntry));  // 插入倒排索引
            F->FileNo = FileNo;
            F->Next = TheCells[pos].InvIndex;
            TheCells[pos].InvIndex = F;
            return pos;
        }
        else
            return -1;  // 同一文件的重复单词，不插入
    }
    static void FileIndex(WList* File, int FileNo, int pos)  //将单词在散列中的位置pos存入文件FileNo对应的索引表
    {
        WList* p = (FileEntry*)malloc(sizeof(struct FileEntry));
        p->Words = pos;
        p->Next = File[FileNo - 1].Next;
        File[FileNo - 1].Next = p;
    }
    double ComputeSim(WList* File, int F1, int F2)  //计算文件F1和F2相似度
    {
       WList* p1 = File[F1 - 1].Next;
       WList* p2 = File[F2 - 1].Next;
       int count_s = 0;
       int count_all = 0;
       while(p1){
           count_all++;
           WList* temp = p2;
           while(temp){
               if(p1->Words == temp->Words){
                   count_s++;
                   break;
               }
               temp = temp->Next;
           }
           p1 = p1->Next;
       }
       while(p2){
           count_all++;
           p2 = p2->Next;
       }
       return (double)100*count_s / (count_all - count_s);
    }
};
