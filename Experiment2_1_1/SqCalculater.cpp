#include <string>
#include <iostream>

using namespace std;

const int MAXSIZE = 100; //顺序栈最大容量

template <typename T>//顺序栈模板类
class SqStack
{//顺序栈的数据成员
    int top; //栈顶指针
    T *data; //元素存储空间
public:
    // 顺序栈的方法声明及重载编译系统默认方法声明:
    SqStack()//构造函数
    {
        data = new T[MAXSIZE]; //分配存储空间
        top = -1; //栈顶指针初始化为-1
    }
    ~SqStack()//析构函数
    {
        delete[] data; //释放存储空间
    }
    bool StackEmpty()//判断栈是否为空
    {
        return (top == -1); //栈为空则返回true
    }
    bool Push(T e)//入栈
    {
        if(top==MAXSIZE-1) //栈满则返回false
            return false;
        data[++top]=e;
        return true;
    }
    bool Pop(T &e)//出栈
    {
        if(top==-1) //栈空则返回false
        return false;
        e=data[top--];
        return true;
    }
    bool GetTop(T &e) //获取栈顶元素
    {
        if(top==-1) //栈空则返回false
        return false;
        e=data[top];
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
    SqStack<char> opStack;

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

//计算后缀表达式
// 评估给定的后缀表达式并返回计算结果
int evaluatePostfix(const string &postfix)
{
    SqStack<int> operandStack; // 操作数栈
    for(int i=0;i<postfix.length();i++)
    {
        char c=postfix[i];

        //如果是操作数就入栈
        // 将从后缀表达式中读取的数字入栈
        if(isdigit(c))
        {
            int d=0;
            while(postfix[i]!='#')
            {
                d=d*10+(postfix[i]-'0');
                i++;
            }
            operandStack.Push(d);
        }
        //如果是运算符，弹出俩个操作数进行运算
        // 进行运算并将结果入栈
        else if(isOperator(c))
        {
            int operand1,operand2;
            operandStack.Pop(operand2);
            operandStack.Pop(operand1);
            int result;

            switch(c)
            {
                case '+':
                    result=operand1+operand2;
                    break;
                case '-':   
                    result=operand1-operand2;
                    break;
                case '*':
                    result=operand1*operand2;
                    break;
                case '/':
                    result=operand1/operand2;
                    break;
            }
            operandStack.Push(result);
        }
    }
    int finalResult; // 存储最终结果
    operandStack.Pop(finalResult); // 弹出最终计算结果
    return finalResult; // 返回最终结果
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