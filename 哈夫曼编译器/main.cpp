#include <iostream>
#include <fstream>
#include <cstring>
#define MAXSIZE 100
 
using namespace std;

//哈夫曼树的存储结构 
typedef struct HaffmanTree{
	double weight;					//权值
	char letter;
	int parent,lChild,rChild;	//结点的双亲、左孩子、右孩子的下标 
}HTNode,*HuffmanTree;			//态分配数组储存哈夫曼树 

typedef char **HuffmanCode;		//动态分配数组储存哈夫曼编码表 

//栈储存结构 
typedef struct{ 
	int *base;		//栈底指针
	int *top;		//栈顶指针
	int stackSize;	//栈的最大容量 
}SqStack; 

//栈初始化 
int InitStack (SqStack &S){
	S.base = new int[MAXSIZE];  //为顺序栈动态分配空间 
	if(!S.base)            
	    //分配失败 
		exit(0);
	S.top = S.base;
	S.stackSize = MAXSIZE;
	return 1;
}

//入栈
int Push(SqStack &S,int elem){
	if(S.top-S.base == S.stackSize)		//栈满 
		return 0;
	*S.top++ = elem;
	return 1;
}

//出栈
int Pop(SqStack &S,int &elem){
	if(S.top == S.base)				//栈空 
		return 0;
	elem = *--S.top;				//取出栈顶元素并出栈 
	return 1;
}

//判断是否为空栈 
int StackEmpty(SqStack &S){
	if(S.top == S.base)		//栈空，返回1 
		return 1;
	else
		return 0;
}

//寻找最小的两个元素           s1<s2
void Select(HuffmanTree &HT,int n,int &s1,int &s2){ 
	int i =1 ,j;
	for(i;i < n && HT[i].parent != 0;++i);  		//找到第一个双亲为0的点 
	j = i;
	for(i = i+1;i < n && HT[i].parent != 0;++i);	//找到第二个双亲为0的点
	if(HT[i].weight < HT[j].weight){			  	//使s1<s2 
		s1 = i;s2 = j;
	}
	else{
		s1 = j;s2 = i;
	}
	while(++i <= n){								//找权值最小的两个点 
		if(HT[i].parent == 0){
			if(HT[i].weight < HT[s1].weight){
				s2 = s1;
				s1 = i;
			}else if(HT[i].weight < HT[s2].weight)
				s2 = i;
		}
	}
}

//建立哈夫曼树
void CreatTree(HuffmanTree &HT,int n) {
	int m;
	if(n <= 1){
		printf("字符个数不足！\n");		
		return;
	}
	m = 2*n-1;
	HT = new HTNode[m+1];		//从1开始，0未用，需要动态分配 m+1 个单元，HT[m]表示根节点 
	for(int i = 1;i <= m;i++){  //将双亲、左孩子、右孩子的下标初始化为0 
		HT[i].parent = 0;
		HT[i].lChild = 0;
		HT[i].rChild = 0;
	}
	
	/*------------初始化n个字符及其权值----------- */
	for(int i = 1;i <= n;i++) {
		cout << "请输入第" << i << "个字符及权值："; 
		cin >> HT[i].letter;
		cin >> HT[i].weight;
		while(!cin){
			cin.clear();		//更改cin的状态标示符
			cin.sync();			//清除缓存区的数据流
			cout << "格式错误, 重新输入\n";
			cin >> HT[i].letter;
			cin >> HT[i].weight;
		}
	}
	
	/*------------创建哈夫曼树----------- */
	int s1,s2;
	for(int i = n+1;i <= m;i++){	//通过n-1次的选择、删除、合并来创建哈夫曼树 
		Select(HT,i-1,s1,s2);		//找出权值最小的两个
		HT[s1].parent = i;
		HT[s2].parent = i;			//将双亲设为i
		
        HT[i].lChild = s1;
		HT[i].rChild = s2;		  //将其作为左右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight;	//双亲的权值为左右孩子权值之和 
	}
}

//初始字符编码
void Code(HuffmanTree HT,HuffmanCode &HC,int n) {
    /*-------------------字初始符编码-----------------------------------*/
    int start,child,parent;
	HC = new char*[n+1];	 			//分配n个字符编码的编码表空间 
	char* cd = new char[n];  			//分配临时存放每个字符编码的动态数组空间 
	cd[n-1] = '\0';         			//编码结束符
	for(int i = 1;i <= n;i++){
		start = n-1;					//start开始指向最后，即编码结束符的位置 
		child = i;				
		parent = HT[i].parent;			//parent指向节点child的双亲节点
		while(parent != 0){
			--start;					//回溯一次start向前指一个位置
			if(HT[parent].lChild == child)	
				cd[start] = '0';		//child为parent的左孩子，生成0 
			else
				cd[start] = '1';		//child为parent的右孩子，生成1 
			child = parent;
			parent = HT[parent].parent;	//继续向上回溯
		}
		HC[i] = new char[n-start];		//为第i个字符编码分配空间
		strcpy(HC[i],&cd[start]); 		//将求得的编码从临时空间cd复制到HC的行列中 
	}
	delete cd;							//释放临时空间
	cout << "对应字符编码为：\n";
	for(int i = 1;i <= n;i++){
		cout << HT[i].letter << ":" << HC[i] << endl; 
	}
	
	/*-------------------------将字符编码写入文件---------------------------------*/
	ofstream fout("code.txt");
	for(int i = 1;i <= n;i++){
		fout << HT[i].letter << ":" << HC[i];
		fout << endl;
	}
}

//对正文编码
void TextCode(HuffmanTree HT,HuffmanCode &HC,int n){
	ifstream file;
	file.open("code_text.txt");
	if(!file){					//判断文件是否打开
		cout << "打开code_text.txt失败!\n";
		exit(0);
	}
	
	ofstream fout("code_result.txt");
	int flag;
	char ch;
	while(file.get(ch)){
		for(int i = 1;i <= n;i++){
			if(ch == HT[i].letter){
				fout << HC[i];
				flag = 1;		//标志flag为1，匹配到初始化的字符 
				break;
			}
			else
				flag = 0;
		}
		if(!flag)
			fout << ch;
	}
	cout << "编码完成\n"
		 << "已初始化的字符由编码代替\n"
		 << "未初始化的字符不进行替换\n";
}

//译码
void Decode(HuffmanTree HT,int n) {
	ifstream file;
	file.open("decode_text.txt");
	if(!file){					//判断文件是否打开
		cout << "打开decode_text.txt失败!\n";
		exit(0);
	}
	
	ofstream fout("decode_result.txt");
	int m = 2*n-1;; //根节点
	char ch;
	while(file.get(ch)){
		if(ch == '1')
			m = HT[m].rChild;
		else if(ch == '0')
			m = HT[m].lChild;
		if(HT[m].lChild == 0 && HT[m].rChild == 0){  //当前字段解码完毕 
			fout << HT[m].letter;
			m = 2*n-1;
		}
	}
	cout << "译码完成\n";
}

//显示哈夫曼树
void DisplayTree(HuffmanTree HT,int n) {
	SqStack S;
	InitStack(S);
	int temp,k;
	int m = 2*n-1;					//根节点 
	while(m != 0 || StackEmpty(S) == 0){
		while(m != 0){
			Push(S,m); 				//入栈 
			m = HT[m].rChild; 		//遍历右子树 	
		} 
		if(!StackEmpty(S)){
			Pop(S,m);				//出栈 
			
			k = 0;temp = m;			//计算离根节点距离，美化输出 
			while(temp){
				temp = HT[temp].parent;
				k++;
			}
			for(int i = 1;i < k;i++){
				printf("    ");
			}
			
			cout << HT[m].weight << endl;
			m = HT[m].lChild; //遍历左子树	
		} 	
	}
}

//显示正文的编码及译码结果
void Result(HuffmanTree HT){
	char ch;
	ifstream fileCode,fileDecode;
	
	/*-----------正文编码结果-------------------*/
	fileCode.open("code_result.txt");
	if(!fileCode){					//判断文件是否打开
		cout << "打开code_result.txt失败!\n";
		exit(0);
	}
	cout << "正文编码结果：\n"; 
	while(fileCode.get(ch)){
		cout << ch;
	}
	cout << endl;
	
	/*-----------正文译码结果-------------------*/
	fileDecode.open("decode_result.txt");
	if(!fileDecode){
		cout << "打开decode_result.txt失败!\n";
		exit(0);
	}
	cout << "\n正文译码结果：\n";
	while(fileDecode.get(ch)){
		cout << ch;
	}
	cout << endl << endl; 
}

//菜单
void menu() {
	cout << "			        哈夫曼编/译码器\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "				1 建立哈夫曼树\n";
	cout << "				2 字符编码\n";
	cout << "				3 译码\n";
	cout << "				4 显示哈夫曼树\n";
	cout << "				5 对正文进行编码\n";
	cout << "				6 显示正文的编码及译码结果\n";
	cout << "				0 退出程序\n";
	cout << "-------------------------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
	int choice,n;
	HuffmanTree Tree;
	HuffmanCode HC;
	while(1){
		menu();
		cout << "\n请选择对应的功能选项进行相应操作：\n";
		cin >> choice;
		switch(choice){
			//建立哈夫曼树
			case 1:
				cout << "输入字符的个数：";
				cin >> n;
				while(!cin){
					cin.clear();
					cin.sync();			//清空流
					cout << "格式错误, 重新输入\n";
					cin >> n;
				}
				CreatTree(Tree,n);
				
				break;
			
			//编码
			case 2:
				if(Tree != NULL)
					Code(Tree,HC,n);
				else
					cout << "还未创建哈夫曼树\n";	
				break;
			
			//译码
			case 3:
				if(Tree != NULL)
					Decode(Tree,n);
				else
					cout << "还未创建哈夫曼树\n";	
				break;
				
			//显示哈夫曼树
			case 4:
				if(Tree != NULL)
					DisplayTree(Tree,n);
				else
					cout << "还未创建哈夫曼树\n";
				break;
			
			//对正文编码 
			case 5:
				if(Tree != NULL)
					TextCode(Tree,HC,n);
				else
					cout << "还未创建哈夫曼树\n";
				break; 
				
			//显示正文的编码及译码结果
			case 6:
				if(Tree != NULL)
					Result(Tree);
				else
					cout << "还未创建哈夫曼树\n";
				break;
			
			case 0:
				exit(0);
			
			default:
				cout << "请输入正确的操作序号！\n";
				break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
