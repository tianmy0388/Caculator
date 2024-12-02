#include <iostream>								// 编译预处理命令
#include <cstdlib>								// 含C函数system()和exit()的声明（stdlib.h与cstdlib是C的头文件）
#include <cctype>								// 含C函数tolower()的声明（ctype.h与cctype是C的头文件）
#include <cmath>								// 数学函数（math.h与cmath是C的头文件）
using namespace std;							// 使用命名空间std
#include "my_calculator.h"						// 计算器类

int main()
{
	char select;								// 用户接受用户回答是否继续

	do
	{
		MyCalculator<double> objExpression;		// 表达式对象21
		cout << "输入表达式:" << endl;
		objExpression.Run();					// 运行表达式
		cout << "是否继续(y/n)?";
		cin >> select;							// 输入用户的选择
		select = tolower(select);				// 大写字母转换为小写字母
		while (select != 'y' && select != 'n')
		{	// 输入有错
			cout << "输入有错，请重新输入(y/n)?";
			cin >> select;						// 输入用户的选择
			select = tolower(select);			// 大写字母转换为小写字母
		}
	} while (select == 'y');
	
	system("PAUSE");							// 调用库函数system()
	return 0;									// 返回值0, 返回操作系统
}
