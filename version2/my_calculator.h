#ifndef __MY_CALCULATOR_H__
#define __MY_CALCULATOR_H__

#include "lk_stack.h"										// 链栈类

// 计算器类模板
template <class ElemType>
class MyCalculator
{
private:
    //  计算器的数据成员:
    LinkStack<ElemType> opnd;
    LinkStack<char> optr;

    // 辅助函数模板:
    int OperPrior(char op);									// 操作符优先级 
    void Get2Operands(ElemType &left, ElemType &right);     // 从栈opnd中退出两个操作数
    void Get1Operand(ElemType &left);                       // 从栈opnd中退出一个操作数
    ElemType Operate(ElemType left, char op, ElemType right);   // 执行运算left op right
    ElemType Operate_factorial(ElemType left);               // 阶乘运算
    bool Is_sin(char t1, char t2);                                        // 判断是否为正弦运算
    ElemType Operate_sin(ElemType left);                     // 正弦运算
    bool Is_cos(char t1, char t2);                                        // 判断是否为余弦运算
    ElemType Operate_cos(ElemType left);                     // 余弦运算
    bool Is_tan(char t1, char t2);                                        // 判断是否为正切运算
    ElemType Operate_tan(ElemType left);                     // 正切运算
    bool IsOperator(char ch);                                   // 判断ch是否为操作符

public:
// 计算器类方法声明:
    MyCalculator(){};										// 无参数的构造函数模板
    virtual ~MyCalculator(){};								// 析构函数模板
    void Run();												// 运算表达式
};

// 计算器类模板的实现部分
template <class ElemType>
int MyCalculator<ElemType>::OperPrior(char op){
    // 操作结果：返回操作符op的优先级
    switch (op)
    {
    case '+':
    case '-':
        return 1;       // + - 优先级为1
    case '*':           
    case '/':
    case '%':           
        return 2;       // * / % 优先级为2
    case '^':           
        return 3;       // ^ 优先级为3
    case '(':
    case ')':
        return 0;       // ( ) 优先级为0       
    case '=':
        return -1;      // = 优先级为-1
    case 's':
    case 'c':
    case 't':
        return 4;       // sin cos tan 优先级为4

    default: return -2; // 其他情况返回-2
    }
}

template <class ElemType>
void MyCalculator<ElemType>::Get2Operands(ElemType &left, ElemType &right){
    // 操作结果：从栈opnd中退出两个操作数
    if (!opnd.Pop(right)) { cout << "表达式有错!" << endl; exit(1); }	// 出现异常	
    if (!opnd.Pop(left)) { cout << "表达式有错!" << endl; exit(2); }	// 出现异常
    //取值同时判断操作是否正常进行
}

template <class ElemType>
void MyCalculator<ElemType>::Get1Operand(ElemType &left){
    // 操作结果：从栈opnd中退出一个操作数
    if (!opnd.Pop(left)) { cout << "表达式有错!" << endl; exit(1); }	// 出现异常	
}

template <class ElemType>
ElemType MyCalculator<ElemType>::Operate(ElemType left, char op, ElemType right){
    // 操作结果：执行运算left op right
    switch (op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        if (right == 0) { cout << "除数为0!" << endl; exit(3); }	// 出现异常
        return left / right;
    case '%':
        if (right == 0) { cout << "除数为0!" << endl; exit(4); }	// 出现异常
        return (long)left % (long)right;
    case '^':
        return pow(left, right);
    }
}

template<class ElemType>
ElemType MyCalculator<ElemType>::Operate_factorial(ElemType left){
    // 操作结果：执行阶乘运算
    if(left < 0){ cout << "阶乘运算对象不能为负数!" << endl; exit(5); } // 阶乘运算对象不能为负数
    if(left == 0) return 1;
    ElemType result = 1;
    for(ElemType i = 1; i <= left; i++){
        result *= i;
    }
    return result;
}

template<class ElemType>
bool MyCalculator<ElemType>::Is_sin(char t1, char t2){
    // 操作结果：判断是否为正弦运算
    if(t1 == 'i'){
        if(t2 == 'n'){
            return true;
        }
    }
    return false;
}

template<class ElemType>
ElemType MyCalculator<ElemType>::Operate_sin(ElemType right){
    // 操作结果：执行正弦运算
    return sin(right);
}

template<class ElemType>
bool MyCalculator<ElemType>::Is_cos(char t1, char t2){
    // 操作结果：判断是否为余弦运算
    if(t1 == 'o'){
        if(t2 == 's'){
            return true;
        }
    }
    return false;
}

template<class ElemType>
ElemType MyCalculator<ElemType>::Operate_cos(ElemType right){
    // 操作结果：执行余弦运算
    return cos(right);
}

template<class ElemType>
bool MyCalculator<ElemType>::Is_tan(char t1, char t2){
    // 操作结果：判断是否为正切运算
    if(t1 == 'a'){
        if(t2 == 'n'){
            return true;
        }
    }
    return false;
}

template<class ElemType>
ElemType MyCalculator<ElemType>::Operate_tan(ElemType right){
    // 操作结果：执行正切运算
    return tan(right);
}

template<class ElemType>
bool MyCalculator<ElemType>::IsOperator(char ch){
    // 操作结果：判断ch是否为操作符
    return (ch == '+' || ch =='!' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')' || ch == '='|| ch == 's' || ch == 'c' || ch == 't');
}

template<class ElemType>
void MyCalculator<ElemType>::Run(){
    // 操作结果：运算表达式
    optr.Clear(); opnd.Clear();		// 清空optr栈与opnd栈
    optr.Push('=');						// 在optr栈中加入一个'='，该字符不起任何作用，只做运算结束的触发器使用于while循环
    ElemType operand;					// 操作数
    char ch;							// 临时字符，从cin缓冲区读入
    char optrTop;                       // optr栈顶元素
    char priorChar;						// 当前输入的前一个字符，如不为操作符，则令其值为'0'，类似编译器读入文本代码的处理方式
    char op;							// 操作符

    priorChar = '=';
    cin >> ch;
    if(!optr.Top(optrTop)){ cout << "表达式有错!" << endl; exit(6); }  // 取出optr栈的栈顶出现异常
    while(!(optrTop == '=' && ch == '=')){          //当栈顶元素为刚才置入的=且cin也读到=时，输入结束
        if(isdigit(ch) && !isdigit(priorChar)){
            ElemType num = 0;
            while(isdigit(ch)){
                num = num * 10 + ch - '0';          //将连续的数字字符转换为数字
                cin >> ch;
            }
            if(ch == '.'){                          //判断小数
                ElemType fraction = 0.1;
                cin >> ch;
                while(isdigit(ch)){
                    num = num + fraction * (ch - '0');
                    fraction *= 0.1;
                    cin >> ch;
                }
            }
            operand = num;
            opnd.Push(operand);                     //将操作数压入栈
            priorChar = '0';                        //前一个字符不是操作符
        }
        else if(!IsOperator(ch)){
            cout << "表达式有错!" << endl; exit(7); // 输入的字符既不是数字也不是操作符
        }
        else if(ch == '-' && !isdigit(priorChar)){ //判断负数，负数的前一个字符不是数字
            ElemType num = 0;
            cin >> ch;
            while(isdigit(ch)){
                num = num * 10 + ch - '0';          //将连续的数字字符转换为数字
                cin >> ch;
            }
            if(ch == '.'){                          //判断小数
                ElemType fraction = 0.1;
                cin >> ch;
                while(isdigit(ch)){
                    num = num + fraction * (ch - '0');
                    fraction *= 0.1;
                    cin >> ch;
                }
            }
            operand = -num;
            opnd.Push(operand);                      //将负数压入栈
            priorChar = '0';                        //前一个字符不是操作符
        }
        else{ // ch为操作符
            if((priorChar == '=' || priorChar == '(') && ch == '+' ){ //这里没有考虑到负数的情况，是因为负数的情况在上面已经处理了
                opnd.Push(0);           //ch为单目运算符+-, 在其前面加上操作数0
                priorChar = '0';        //在其前面加上操作数0，'0'作为前一字符
            }
            if(optrTop == ')'&& ch == '(' || optrTop == '='&& ch == ')' || optrTop == '(' && ch =='='){ //表达式有错
                cout << "表达式有错!" << endl; exit(8);
            }else if(ch == 's' || ch == 'c' || ch == 't'){ //三角函数运算
                if(priorChar == '0'){ //三角函数运算符前面不能为数字
                    cout << "三角函数运算符前面不能为数字!" << endl; exit(9);
                }else{
                    char t1, t2;
                    cin >> t1 >> t2;
                    if(!Is_sin(t1,t2)&&!Is_cos(t1,t2)&&!Is_tan(t1,t2)){ //判断是否为三角函数运算
                        cout << "表达式有错!" << endl; exit(10);
                    }else{
                        optr.Push(ch);
                        priorChar = ch;
                        cin >> ch;
                    }
                }
            }
            else if(ch=='!'){ //阶乘运算
                if(priorChar != '0'){ //阶乘运算对象不能为符号
                    cout << "阶乘运算对象不能为符号!" << endl; exit(11);
                }else{
                    opnd.Pop(operand); //取出栈顶元素
                    if(operand < 0){ //阶乘运算对象不能为负数
                        cout << "阶乘运算对象不能为负数!" << endl; exit(12);
                    }else{
                        ElemType result = Operate_factorial(operand);
                        opnd.Push(result);
                        priorChar = '0';
                        cin >> ch;
                    }
                }
            }
            else if(optrTop == '(' && ch == ')'){  //括号闭合，去括号进行运算
                if(!optr.Pop(optrTop)){ cout << "表达式有错!" << endl; exit(13); } //运算符栈空
                cin >> ch;
                priorChar = ')';
            }else if(ch == '(' || OperPrior(optrTop) < OperPrior(ch)){ //optrTop为(,或optrTop比ch的优先级低，这时仍然不用做任何计算，按顺序入栈即可
                optr.Push(ch);
                priorChar = ch;
                cin >> ch;
            }else{ //optrTop的优先级大于或等于ch的优先级，这时必须出栈做一次运算，结果入操作数栈
                if(!optr.Pop(op)){ cout << "表达式有错!" << endl; exit(14); } //运算符栈空
                if(op == 's' || op == 'c' || op == 't'){ //三角函数运算
                    Get1Operand(operand);
                    if(op == 's'){
                        operand = Operate_sin(operand);
                    }else if(op == 'c'){
                        operand = Operate_cos(operand);
                    }else if(op == 't'){
                        operand = Operate_tan(operand);
                    }
                    opnd.Push(operand);
                }else{
                    ElemType left, right;
                    Get2Operands(left, right);
                    opnd.Push(Operate(left, op, right));
                }
                
            }  
        }
        if(!optr.Top(optrTop)){ cout << "表达式有错!" << endl; exit(15); } //访问optr栈的栈顶出现异常，栈空
    }
    if(!opnd.Top(operand)){ cout << "表达式有错!" << endl; exit(16); } //出现异常，无得数
    cout << "结果为：" << operand << endl;
}


#endif