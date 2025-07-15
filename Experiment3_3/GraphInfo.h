
//弧信息
template<typename T>
struct ArcInfo {
    T From;//起点
    T To;//终点
};

//弧结点
template<typename T>
struct ArcNode {
    int adjvex;//临接点位置
    int weight;//权重
    struct ArcNode<T> *nextarc;
};

//质点结点
template<typename T>
struct VNode {
    T data;
    int in;
    ArcNode<T> *firstarc;
};
