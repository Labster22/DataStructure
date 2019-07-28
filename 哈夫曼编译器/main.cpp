#include <iostream>
#include <fstream>
#include <cstring>
#define MAXSIZE 100
 
using namespace std;

//���������Ĵ洢�ṹ 
typedef struct HaffmanTree{
	double weight;					//Ȩֵ
	char letter;
	int parent,lChild,rChild;	//����˫�ס����ӡ��Һ��ӵ��±� 
}HTNode,*HuffmanTree;			//̬�������鴢��������� 

typedef char **HuffmanCode;		//��̬�������鴢������������ 

//ջ����ṹ 
typedef struct{ 
	int *base;		//ջ��ָ��
	int *top;		//ջ��ָ��
	int stackSize;	//ջ��������� 
}SqStack; 

//ջ��ʼ�� 
int InitStack (SqStack &S){
	S.base = new int[MAXSIZE];  //Ϊ˳��ջ��̬����ռ� 
	if(!S.base)            
	    //����ʧ�� 
		exit(0);
	S.top = S.base;
	S.stackSize = MAXSIZE;
	return 1;
}

//��ջ
int Push(SqStack &S,int elem){
	if(S.top-S.base == S.stackSize)		//ջ�� 
		return 0;
	*S.top++ = elem;
	return 1;
}

//��ջ
int Pop(SqStack &S,int &elem){
	if(S.top == S.base)				//ջ�� 
		return 0;
	elem = *--S.top;				//ȡ��ջ��Ԫ�ز���ջ 
	return 1;
}

//�ж��Ƿ�Ϊ��ջ 
int StackEmpty(SqStack &S){
	if(S.top == S.base)		//ջ�գ�����1 
		return 1;
	else
		return 0;
}

//Ѱ����С������Ԫ��           s1<s2
void Select(HuffmanTree &HT,int n,int &s1,int &s2){ 
	int i =1 ,j;
	for(i;i < n && HT[i].parent != 0;++i);  		//�ҵ���һ��˫��Ϊ0�ĵ� 
	j = i;
	for(i = i+1;i < n && HT[i].parent != 0;++i);	//�ҵ��ڶ���˫��Ϊ0�ĵ�
	if(HT[i].weight < HT[j].weight){			  	//ʹs1<s2 
		s1 = i;s2 = j;
	}
	else{
		s1 = j;s2 = i;
	}
	while(++i <= n){								//��Ȩֵ��С�������� 
		if(HT[i].parent == 0){
			if(HT[i].weight < HT[s1].weight){
				s2 = s1;
				s1 = i;
			}else if(HT[i].weight < HT[s2].weight)
				s2 = i;
		}
	}
}

//������������
void CreatTree(HuffmanTree &HT,int n) {
	int m;
	if(n <= 1){
		printf("�ַ��������㣡\n");		
		return;
	}
	m = 2*n-1;
	HT = new HTNode[m+1];		//��1��ʼ��0δ�ã���Ҫ��̬���� m+1 ����Ԫ��HT[m]��ʾ���ڵ� 
	for(int i = 1;i <= m;i++){  //��˫�ס����ӡ��Һ��ӵ��±��ʼ��Ϊ0 
		HT[i].parent = 0;
		HT[i].lChild = 0;
		HT[i].rChild = 0;
	}
	
	/*------------��ʼ��n���ַ�����Ȩֵ----------- */
	for(int i = 1;i <= n;i++) {
		cout << "�������" << i << "���ַ���Ȩֵ��"; 
		cin >> HT[i].letter;
		cin >> HT[i].weight;
		while(!cin){
			cin.clear();		//����cin��״̬��ʾ��
			cin.sync();			//�����������������
			cout << "��ʽ����, ��������\n";
			cin >> HT[i].letter;
			cin >> HT[i].weight;
		}
	}
	
	/*------------������������----------- */
	int s1,s2;
	for(int i = n+1;i <= m;i++){	//ͨ��n-1�ε�ѡ��ɾ�����ϲ��������������� 
		Select(HT,i-1,s1,s2);		//�ҳ�Ȩֵ��С������
		HT[s1].parent = i;
		HT[s2].parent = i;			//��˫����Ϊi
		
        HT[i].lChild = s1;
		HT[i].rChild = s2;		  //������Ϊ���Һ���
        HT[i].weight = HT[s1].weight + HT[s2].weight;	//˫�׵�ȨֵΪ���Һ���Ȩֵ֮�� 
	}
}

//��ʼ�ַ�����
void Code(HuffmanTree HT,HuffmanCode &HC,int n) {
    /*-------------------�ֳ�ʼ������-----------------------------------*/
    int start,child,parent;
	HC = new char*[n+1];	 			//����n���ַ�����ı����ռ� 
	char* cd = new char[n];  			//������ʱ���ÿ���ַ�����Ķ�̬����ռ� 
	cd[n-1] = '\0';         			//���������
	for(int i = 1;i <= n;i++){
		start = n-1;					//start��ʼָ����󣬼������������λ�� 
		child = i;				
		parent = HT[i].parent;			//parentָ��ڵ�child��˫�׽ڵ�
		while(parent != 0){
			--start;					//����һ��start��ǰָһ��λ��
			if(HT[parent].lChild == child)	
				cd[start] = '0';		//childΪparent�����ӣ�����0 
			else
				cd[start] = '1';		//childΪparent���Һ��ӣ�����1 
			child = parent;
			parent = HT[parent].parent;	//�������ϻ���
		}
		HC[i] = new char[n-start];		//Ϊ��i���ַ��������ռ�
		strcpy(HC[i],&cd[start]); 		//����õı������ʱ�ռ�cd���Ƶ�HC�������� 
	}
	delete cd;							//�ͷ���ʱ�ռ�
	cout << "��Ӧ�ַ�����Ϊ��\n";
	for(int i = 1;i <= n;i++){
		cout << HT[i].letter << ":" << HC[i] << endl; 
	}
	
	/*-------------------------���ַ�����д���ļ�---------------------------------*/
	ofstream fout("code.txt");
	for(int i = 1;i <= n;i++){
		fout << HT[i].letter << ":" << HC[i];
		fout << endl;
	}
}

//�����ı���
void TextCode(HuffmanTree HT,HuffmanCode &HC,int n){
	ifstream file;
	file.open("code_text.txt");
	if(!file){					//�ж��ļ��Ƿ��
		cout << "��code_text.txtʧ��!\n";
		exit(0);
	}
	
	ofstream fout("code_result.txt");
	int flag;
	char ch;
	while(file.get(ch)){
		for(int i = 1;i <= n;i++){
			if(ch == HT[i].letter){
				fout << HC[i];
				flag = 1;		//��־flagΪ1��ƥ�䵽��ʼ�����ַ� 
				break;
			}
			else
				flag = 0;
		}
		if(!flag)
			fout << ch;
	}
	cout << "�������\n"
		 << "�ѳ�ʼ�����ַ��ɱ������\n"
		 << "δ��ʼ�����ַ��������滻\n";
}

//����
void Decode(HuffmanTree HT,int n) {
	ifstream file;
	file.open("decode_text.txt");
	if(!file){					//�ж��ļ��Ƿ��
		cout << "��decode_text.txtʧ��!\n";
		exit(0);
	}
	
	ofstream fout("decode_result.txt");
	int m = 2*n-1;; //���ڵ�
	char ch;
	while(file.get(ch)){
		if(ch == '1')
			m = HT[m].rChild;
		else if(ch == '0')
			m = HT[m].lChild;
		if(HT[m].lChild == 0 && HT[m].rChild == 0){  //��ǰ�ֶν������ 
			fout << HT[m].letter;
			m = 2*n-1;
		}
	}
	cout << "�������\n";
}

//��ʾ��������
void DisplayTree(HuffmanTree HT,int n) {
	SqStack S;
	InitStack(S);
	int temp,k;
	int m = 2*n-1;					//���ڵ� 
	while(m != 0 || StackEmpty(S) == 0){
		while(m != 0){
			Push(S,m); 				//��ջ 
			m = HT[m].rChild; 		//���������� 	
		} 
		if(!StackEmpty(S)){
			Pop(S,m);				//��ջ 
			
			k = 0;temp = m;			//��������ڵ���룬������� 
			while(temp){
				temp = HT[temp].parent;
				k++;
			}
			for(int i = 1;i < k;i++){
				printf("    ");
			}
			
			cout << HT[m].weight << endl;
			m = HT[m].lChild; //����������	
		} 	
	}
}

//��ʾ���ĵı��뼰������
void Result(HuffmanTree HT){
	char ch;
	ifstream fileCode,fileDecode;
	
	/*-----------���ı�����-------------------*/
	fileCode.open("code_result.txt");
	if(!fileCode){					//�ж��ļ��Ƿ��
		cout << "��code_result.txtʧ��!\n";
		exit(0);
	}
	cout << "���ı�������\n"; 
	while(fileCode.get(ch)){
		cout << ch;
	}
	cout << endl;
	
	/*-----------����������-------------------*/
	fileDecode.open("decode_result.txt");
	if(!fileDecode){
		cout << "��decode_result.txtʧ��!\n";
		exit(0);
	}
	cout << "\n������������\n";
	while(fileDecode.get(ch)){
		cout << ch;
	}
	cout << endl << endl; 
}

//�˵�
void menu() {
	cout << "			        ��������/������\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "				1 ������������\n";
	cout << "				2 �ַ�����\n";
	cout << "				3 ����\n";
	cout << "				4 ��ʾ��������\n";
	cout << "				5 �����Ľ��б���\n";
	cout << "				6 ��ʾ���ĵı��뼰������\n";
	cout << "				0 �˳�����\n";
	cout << "-------------------------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
	int choice,n;
	HuffmanTree Tree;
	HuffmanCode HC;
	while(1){
		menu();
		cout << "\n��ѡ���Ӧ�Ĺ���ѡ�������Ӧ������\n";
		cin >> choice;
		switch(choice){
			//������������
			case 1:
				cout << "�����ַ��ĸ�����";
				cin >> n;
				while(!cin){
					cin.clear();
					cin.sync();			//�����
					cout << "��ʽ����, ��������\n";
					cin >> n;
				}
				CreatTree(Tree,n);
				
				break;
			
			//����
			case 2:
				if(Tree != NULL)
					Code(Tree,HC,n);
				else
					cout << "��δ������������\n";	
				break;
			
			//����
			case 3:
				if(Tree != NULL)
					Decode(Tree,n);
				else
					cout << "��δ������������\n";	
				break;
				
			//��ʾ��������
			case 4:
				if(Tree != NULL)
					DisplayTree(Tree,n);
				else
					cout << "��δ������������\n";
				break;
			
			//�����ı��� 
			case 5:
				if(Tree != NULL)
					TextCode(Tree,HC,n);
				else
					cout << "��δ������������\n";
				break; 
				
			//��ʾ���ĵı��뼰������
			case 6:
				if(Tree != NULL)
					Result(Tree);
				else
					cout << "��δ������������\n";
				break;
			
			case 0:
				exit(0);
			
			default:
				cout << "��������ȷ�Ĳ�����ţ�\n";
				break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
