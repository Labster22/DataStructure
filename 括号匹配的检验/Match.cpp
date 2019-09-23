#include<iostream>
#define MAXSIZE 100


using namespace std;

//�洢�ṹ�� 
typedef struct{
	char *base;		//ջ��ָ�� 
	char *top;		//ջ��ָ�� 
	int stackSize;	//ջ��������� 
}SqStack;

//��ʼ��ջ 
int InitStack(SqStack &S){
	S.base = new char[MAXSIZE];  //Ϊ˳��ջ��̬����ռ� 
	if(!S.base)                  //����ʧ�� 
		exit(0);
	S.top = S.base;
	S.stackSize = MAXSIZE;
	return 1;
}

//��ջ
int Push(SqStack &S,char elem){
	if(S.top-S.base == S.stackSize)		//ջ�� 
		return 0;
	*S.top++ = elem;
	return 1;
}
 
//��ջ 
int Pop(SqStack &S,char &elem){
	if(S.top == S.base)				//ջ�� 
		return 0;
	elem = *--S.top;
	return 1;
}

//ȡջ��Ԫ��
int GetTop(SqStack &S){
	if(S.top != S.base)
		return *(S.top-1);
}

//�ж�ջ�Ƿ�Ϊ�� 
int StackEmpty(SqStack &S){
	if(S.top == S.base)		//ջ�գ�����1��˵��ջ��Ԫ����ȫ����ջ��û��Ԫ�ؽ�ջ��û��δƥ���ǰ���� 
		return 1;
	else
		return 0;
}

//ƥ���ַ�
int Match(SqStack &S){
	InitStack(S);	//��ʼ��ջ 
	char elem;
	int flag = 1;	//���ƥ���� 
	cout << "�������ַ�������#����Ϊ������־��\n"; 
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

//�˵�
void menu(){
	cout << "			        ����ƥ��\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "				1 ���з���ƥ��\n";
	cout << "				0 �˳�����\n";
	cout << "-------------------------------------------------------------------------------\n";
}
 
int main(){ 
	int choice,answer; 
	SqStack S;
	while(1){
		system("cls");
		menu();
		cout << "��ѡ���Ӧ�Ĺ���ѡ�������Ӧ������\n";
		cin >> choice;
		while(!cin){
			cout << "��������ȷ�Ĳ�����ţ�";
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
				cout << "��������ȷ�Ĳ������:\n"; 
		}
		system("pause");
	}
	return 0;
}
