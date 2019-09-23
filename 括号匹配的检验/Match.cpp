#include<iostream>
#define MAXSIZE 100


using namespace std;

//存储结构体 
typedef struct{
	char *base;		//栈底指针 
	char *top;		//栈顶指针 
	int stackSize;	//栈的最大容量 
}SqStack;

//初始化栈 
int InitStack(SqStack &S){
	S.base = new char[MAXSIZE];  //为顺序栈动态分配空间 
	if(!S.base)                  //分配失败 
		exit(0);
	S.top = S.base;
	S.stackSize = MAXSIZE;
	return 1;
}

//入栈
int Push(SqStack &S,char elem){
	if(S.top-S.base == S.stackSize)		//栈满 
		return 0;
	*S.top++ = elem;
	return 1;
}
 
//出栈 
int Pop(SqStack &S,char &elem){
	if(S.top == S.base)				//栈空 
		return 0;
	elem = *--S.top;
	return 1;
}

//取栈顶元素
int GetTop(SqStack &S){
	if(S.top != S.base)
		return *(S.top-1);
}

//判断栈是否为空 
int StackEmpty(SqStack &S){
	if(S.top == S.base)		//栈空，返回1，说明栈中元素已全部出栈或没有元素进栈，没有未匹配的前括号 
		return 1;
	else
		return 0;
}

//匹配字符
int Match(SqStack &S){
	InitStack(S);	//初始化栈 
	char elem;
	int flag = 1;	//标记匹配结果 
	cout << "请输入字符串，以#号作为结束标志：\n"; 
	cin >> elem;
	while(elem != '#' && flag){
		switch(elem){
			case '[':
			case '(':
			case '{':
				Push(S,elem);
				break;
			case ')':
				if(!StackEmpty(S) && GetTop(S) == '(')
					Pop(S,elem);
				else 
					flag = 0;
				break;
			case ']':
				if(!StackEmpty(S) && GetTop(S) == '[')
					Pop(S,elem);
				else
					flag = 0;
				break;
			case '}':
				if(!StackEmpty(S) && GetTop(S) == '{')
					Pop(S,elem);
				else
					flag = 0;
				break;
		}
		cin >> elem;
	}
	if(StackEmpty(S) && flag)
		return 1;
	else
		return 0; 
}

//菜单
void menu(){
	cout << "			        括号匹配\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "				1 进行符号匹配\n";
	cout << "				0 退出程序\n";
	cout << "-------------------------------------------------------------------------------\n";
}
 
int main(){ 
	int choice,answer; 
	SqStack S;
	while(1){
		system("cls");
		menu();
		cout << "请选择对应的功能选项进行相应操作：\n";
		cin >> choice;
		while(!cin){
			cout << "请输入正确的操作序号：";
			cin.clear();
			cin.sync();
			cin >> choice;
		}
		switch(choice){
			case 1:
				answer = Match(S);
				if(answer)
					cout << "True\n";
				else
					cout << "False\n";
				break;
			case 0:
				exit(0); 
				break;
			default:
				cout << "请输入正确的操作序号:\n"; 
		}
		system("pause");
	}
	return 0;
}
