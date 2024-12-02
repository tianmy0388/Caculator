#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"														// 结点类模板

// 链栈类模板
template<class ElemType>
class LinkStack 
{
protected:
// 数据成员:
	Node<ElemType> *top;												// 栈顶指针
	int count;															// 元素个数

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	LinkStack();														// 无参数的构造函数模板
	virtual ~LinkStack();												// 析构函数模板
	int Length() const;													// 求栈长度			 
	bool Empty() const;													// 判断栈是否为空
	void Clear();														// 将栈清空
	void Traverse(void (*visit)(const ElemType &)) const ;				// 遍历栈
	bool Push(const ElemType &e);										// 入栈
	bool Top(ElemType &e) const;										// 返回栈顶元素
	bool Pop(ElemType &e);												// 出栈
	bool Pop();															// 出栈
	LinkStack(const LinkStack<ElemType> &source);						// 复制构造函数模板
	LinkStack<ElemType> &operator =(const LinkStack<ElemType> &source);	// 重载赋值运算符
};


// 链栈类模板的实现部分

template<class ElemType>
LinkStack<ElemType>::LinkStack()
// 操作结果：构造一个空栈表
{
	top = NULL;															// 构造栈顶指针，初始为空
	count = 0;															// 初始化元素个数
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
// 操作结果：销毁栈
{
	Clear();															// 清空栈，参见Clear()
}

template <class ElemType>
int LinkStack<ElemType>::Length() const
// 操作结果：返回栈元素个数
{
	return count;														// count表示栈元素个数，通过pop和push实时维护
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
	return count == 0;													// count == 0表示栈为空
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// 操作结果：清空栈
{
	while (!Empty())
	{	// 表栈非空，则出栈
		Pop();															// 出栈
	}
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void (*visit)(const ElemType &)) const
//这个函数定义及作为参数的函数与教材上的格式类似，此处不必细究。
//不过，这里隐含着一个错误，请试着找出这个错误。
// 操作结果：从栈底到栈顶依次对栈的每个元素调用函数(*visit)
{
	Node<ElemType> *temPtr;												// 临时指针变量
	LinkStack<ElemType> temS;											// 临时栈,temS中元素顺序与当前栈元素顺序相反
	for (temPtr = top; temPtr != NULL; temPtr = temPtr->next)
	{	// 用temPtr依次指向当前栈的每个元素
		temS.Push(temPtr->data);										// 对当前栈的每个元素入栈到temS中
	}
	//这里实际上在没破坏栈的结构的前提下对栈的每一个元素进行了访问
	for (temPtr = temS.top; temPtr != NULL; temPtr = temPtr->next)
	{	// 用temPtr从栈顶到栈底依次指向栈temS的每个元素
		(*visit)(temPtr->data);											// 对栈temS的每个元素调用函数(*visit)
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Push(const ElemType &e)
// 操作结果：将元素e追加到栈顶,如成功则返加true,否则如动态内存已耗尽
//	将返回false
{
	Node<ElemType> *newTop = new Node<ElemType>(e, top);
	if (newTop == NULL) 
	{	// 动态内存耗尽
		return false;													// 失败
	}
	else
	{	// 操作成功
		top = newTop;													// 物理结构：newTop -> top -> oldContent
		count++;														// 入栈成功后元素个数加1 
		return true;													// 成功
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Top(ElemType &e) const
// 操作结果：如栈非空,用e返回栈顶元素,返回true,否则返回false
{
	if(Empty())
	{	// 栈空
		return false;													// 失败
	}
	else
	{	// 栈非空,操作成功
		e = top->data;													// 用e返回栈顶元素
		return true;													// 成功
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Pop(ElemType &e)
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,返回true,否则
//	返回false
{
	if (Empty())
	{	// 栈空
		return false;													// 失败
	}
	else
	{	// 操作成功
		Node<ElemType> *oldTop = top;									// 旧栈顶
		e = oldTop->data;												// 用e返回栈顶元素
		top = oldTop->next;												// top指向新栈顶
		delete oldTop;													// 删除旧栈顶
		count--;														// 出栈成功后元素个数自减1
		return true;													// 功能
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Pop()
// 操作结果：如栈非空,删除栈顶元素,返回true,否则返回false
{
	if (Empty())
	{	// 栈空
		return false;													// 失败
	}
	else
	{	// 操作成功
		Node<ElemType> *oldTop = top;									// 旧栈顶
		top = oldTop->next;												// top指向新栈顶
		delete oldTop;													// 删除旧栈顶
		count--;														// 出栈成功后元素个数自减1
		return true;													// 功能
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &source) 
// 操作结果：由栈source构造新栈——复制构造函数模板
{
	//克隆函数
	if (source.Empty())
	{	// source为空
		top = NULL;														// 构造栈顶指针
		count = 0;														// 初始化元素个数
	}
	else 
	{	// source非空,复制栈
		top = new Node<ElemType>(source.top->data);						// 生成当前栈项
		count = source.count;											// 栈元素个数
		Node<ElemType> *buttomPtr = top;								// 当前栈底指针
		for (Node<ElemType> *temPtr = source.top->next; temPtr != NULL; temPtr = temPtr->next)
		{	// 用temPtr依次指向其余元素
			buttomPtr->next = new Node<ElemType>(temPtr->data);			// 向栈底追加元素	
			buttomPtr = buttomPtr->next;								// buttomPtr指向新栈底
		}
		//类似遍历函数
	}
}


template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &source)
// 操作结果：将栈source赋值给当前栈——重载赋值运算符
{
	//很类似于上面的克隆函数
	if (&source != this)
	{
		if (source.Empty())
		{	// source为空
			top = NULL;													// 构造栈顶指针
			count = 0;													// 初始化元素个数
		}
		else 
		{	// source非空,复制栈
			Clear();													// 清空当前栈
			top = new Node<ElemType>(source.top->data);					// 生成当前栈项
			count = source.count;										// 栈元素个数
			Node<ElemType> *buttomPtr = top;							// 当前栈底指针
			for (Node<ElemType> *temPtr = source.top->next; temPtr != NULL; temPtr = temPtr->next)
			{	// 用temPtr依次指向其余元素
				buttomPtr->next = new Node<ElemType>(temPtr->data);		// 向栈底追加元素	
				buttomPtr = buttomPtr->next;							// buttomPtr指向新栈底
			}
		}
	}
	return *this;
}

#endif