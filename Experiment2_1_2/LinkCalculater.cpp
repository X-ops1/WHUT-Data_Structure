#include <string>
#include <iostream>

using namespace std;

template <typename T>
class LinkStack;//先声明
template <typename T>
class Node
{//数据成员
    friend class LinkStack<T>;
    T data;
    Node<T> *next;
public:
    //构造函数
    Node();//无参数的构造函数
    Node(T item,Node<T> *next=NULL):data(item),next(next){};//已知数据元素值和指针建立结构
};

template <typename T>
class LinkStack
{
//单链表的数据成员
    Node<T> *head;  // 链栈头结点指针
public:
//链栈类的函数成员
    LinkStack()//构造函数
    {
        head=NULL;
    }
    ~LinkStack()//析构函数
    {
        while(head!=NULL)
        {
            Node<T> *p=head;
            head=head->next;
            delete p;
        }
    }
    bool StackEmpty()//判断栈是否为空
    {
        return head==NULL;
    }
    bool Push(T e)//入栈
    {
        Node<T> *p=new Node<T>(e,head);
        head=p;
        return true;
    }
    bool Pop(T &e)//出栈
    {
        if(head==NULL)
        {
            return false;
        }
        e=head->data;
        Node<T> *p=head;
        head=head->next;
        delete p;
        return true;
    }
    bool GetTop(T &e)//取栈顶元素
    {
        if(head==NULL)
        {
            return false;
        }
        e=head->data;
        return true;
    }
};

//获取运算符优先级
static int precedence(char op)
{
    if(op=='+'||op=='-') return 1;
    if(op=='*'||op=='/') return 2;
    return 0;
}

//判断是否为运算符
static bool isOperator(char c)
{
    return c=='+'||c=='-'||c=='*'||c=='/';
}

//将中缀表达式转化为后缀表达式
string infixToPostfix(const string &infix)
{
    string postfix;
    LinkStack<char> opStack;

    for(int i=0;i<infix.length();i++)
    {
        char c=infix[i];

        //如果是操作数，直接输出到后缀表达式
        if(isdigit(c))
        {
             while(infix[i]>='0'&&infix[i]<='9')
            {
                postfix+=infix[i];
                i++;
            }
            i--;
            postfix+='#';//标记操作数结束
        }
        //如果是左括号，压入栈
        else if(c=='(')
        {
            opStack.Push(c);
        }
        //如果是右括号，弹出栈中的运算符并输出到后缀表达式，直到遇到左括号
        else if(c==')')
        {
            char topOp;
            while(opStack.GetTop(topOp)&&topOp!='(')
            {
                postfix+=topOp;
                opStack.Pop(topOp);
            }
            opStack.Pop(topOp);//弹出左括号
        }
        //如果是运算符，比较其优先级，并弹出栈中的运算符，直到栈顶运算符优先级低于当前运算符
        else if(isOperator(c))
        {
            char topOp;
            while(opStack.GetTop(topOp)&&precedence(topOp)>=precedence(c))
            {
                postfix+=topOp;
                opStack.Pop(topOp);
            }
            opStack.Push(c);
        }
    }

    //弹出栈中剩余的运算符
    char topOp;
    while(opStack.GetTop(topOp))
    {
        postfix+=topOp;
        opStack.Pop(topOp);
    }

    return postfix;
}


//判断是否为运算符
bool ISOperator(char c)
{
    return c=='+'||c=='-'||c=='*'||c=='/';
}

//计算后缀表达式
int evaluatePostfix(const string &postfix)
{
    LinkStack<int> operandStack; // 创建一个操作数栈
    for(int i=0;i<postfix.length();i++)
    {
        char c=postfix[i];

        //如果是操作数就入栈
        if(isdigit(c))
        {
             int d=0;
            while(postfix[i]!='#')
            {
                d=d*10+(postfix[i]-'0');
                i++;
            }
            operandStack.Push(d); // 将操作数压入栈中
        }
        //如果是运算符，弹出俩个操作数进行运算
        else if(ISOperator(c))
        {
            int operand1,operand2; // 存储弹出的操作数
            operandStack.Pop(operand2); // 弹出第二个操作数
            operandStack.Pop(operand1); // 弹出第一个操作数
            int result; // 存储运算结果

            switch(c)
            {
                case '+':
                    result=operand1+operand2; // 加法运算
                    break;
                case '-':   
                    result=operand1-operand2; // 减法运算
                    break;
                case '*':
                    result=operand1*operand2; // 乘法运算
                    break;
                case '/':
                    result=operand1/operand2; // 除法运算
                    break;
            }
            operandStack.Push(result); // 将运算结果压入栈中
        }
    }
    int finalResult; // 存储最终计算结果
    operandStack.Pop(finalResult); // 弹出最终结果
    return finalResult; // 返回计算结果
}

int main()
{
    string infixExpression;
    cout << "请输入中缀表达式（没有空格，以=结束）：" << endl;
    cin >> infixExpression;
    
    //去掉末尾的等号
    infixExpression.pop_back();

    //转换为后缀表达式
    string postfixExpression = infixToPostfix(infixExpression);
    cout<<"后缀表达式为："<<postfixExpression<<endl;

    //计算后缀表达式的值
    int result = evaluatePostfix(postfixExpression);
    cout<<"计算结果为："<<result<<endl;

    return 0;
}