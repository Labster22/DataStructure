#include<iostream>

using namespace std;

//存储结构体
typedef struct LNode{
	string isbn;		//图书的ISBN码 
	string name;		//书名 
	double price;		//价格 
	struct LNode *next;
}LNode,*LinkList;
 
//菜单
void menu(){
	cout << "			        图书管理系统\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "				1 创建链表\n";
	cout << "				2 输入图书ISBN查找图书\n";
	cout << "				3 插入图书\n";
	cout << "				4 输入ISBN删除图书\n";
	cout << "				5 修改图书信息\n";
	cout << "				6 打印所有图书\n";
	cout << "				0 退出程序\n";
	cout << "-------------------------------------------------------------------------------\n";
}

//初始化
int InitList(LinkList &List){
	List = new LNode;				//生产新的头结点 
	List->next = NULL;				//头结点的指针域为空 
	return 1;
} 

//创建链表
void CreateList(LinkList &List){
	LinkList new_node,rear;
	rear = List;                    		//保存尾节点 
	char juge = 'y';                    	//判断是否继续输入 
	while(juge == 'y'){
			cout << "请输入图书的ISBN、名字和价格：\n";
			new_node = new LNode;									//每次重新申请新的节点空间 
			cin >> new_node->isbn >> new_node->name >> new_node->price;
			if(cin){
				new_node->next = NULL;									//将新建节点的指针域置为空 
				rear->next = new_node;									//连接新建的节点
				rear = new_node;										//重新指向尾节点 
				cout << "是否继续输入(y or n)?\n";
				cin >> juge;
			}
			else{
				cin.clear();
				cin.sync();			//清空流   
				cout << "格式错误, 重新输入\n";	
			}
	}
}

//打印所有图书信息 
void PrintList(LinkList List){
	LinkList print;     		//print指向所要打印的结点 
	print = List->next;
	while(print){
		cout << print->isbn << " " << print->name << " " << print->price << endl;
		print = print->next;
	}
}

//查找图书 
void SearchList(LinkList &List,string isbn,string name){
	LinkList sear; 
	sear = List->next;
	cout << "输入ISBN:"; 
	cin >> isbn;
	while(sear && sear->isbn != isbn)
		sear = sear->next; 
	if(!sear)
		cout << "图书不存在\n";
	else
		cout << sear->isbn << " " << sear->name << " " << sear->price << endl;
}

//插入图书
int InsertList(LinkList &List,int loc){
	LinkList inser = List,new_node;
	int i = 0;
	while(inser && i < loc-1){
		inser = inser->next;
		++i;
	}
	if(!inser || i > loc-1)
		return 0;
	new_node = new LNode;
	cout << "输入图书的ISBN、书名和价格：\n";
	cin >> new_node->isbn >> new_node->name >> new_node->price;
	new_node->next = inser->next;
	inser->next = new_node;
	return 1;
} 

//删除图书 
int DeleteList(LinkList &List,string isbn){
	LinkList del = List,pre;   //pre保存要删除节点的前一个 
	while(del && del->isbn != isbn){
		pre = del;
		del = del->next;
	}
	if(!del)
		return 0;
	pre->next = del->next;
	delete del;
	return 1;
}

//修改图书信息 
int ChangeList(LinkList &List,string isbn){
	LinkList alter; 
	alter = List;
	while(alter && alter->isbn != isbn){
		alter = alter->next;
	}
	if(!alter)
		return 0;
	cout << "修改图书的isbn、名字和价格为：";
	string name;
	double price;
	cin >> isbn >> name >> price;
	if(cin){
		alter->isbn = isbn;
		alter->name = name;
		alter->price = price;
		return 1;
	}
	else{
		cin.clear();
		cin.sync();		//清空流  
		cout << "格式错误,";
		return 0; 
	}
}


int main(){
	LinkList List;
	InitList(List);
	int choice;
	string name = "0",isbn = "0",price = "0";   //将需要图书的信息初始化
	menu();
	cout << "\n请选择对应的功能选项进行相应操作：\n";              
	cin >> choice;
	while(1){
		switch(choice){
			 //创建链表
			case 1:
				if(List->next != NULL){                        //头结点指针域不为空即为已初始化过 
					cout << "顺序表已经初始化，再次初始化将清除原有数据。是否继续  (y/n):";
					char juge1;
					cin >> juge1;
					while(1){
						if(juge1 == 'y'){
							CreateList(List);								 //重新创建链表
							break; 
						}
						else if(juge1 == 'n'){
							break;
						}
						else{
							cout << "是否继续  (y/n):";					//输入除y与n之外的数的解决方法			      
							cin >> juge1;
						}
					}
				}
				else{
					CreateList(List);										
					break;
				}
				break;	
			//查找图书 	
			case 2: 												 
				if(List->next){
					char juge2 = 'y';
					while(1){
						if(juge2 == 'y'){
							SearchList(List,isbn,name);											
							cout << "是否继续查询？(y/n)\n";
							cin >> juge2;
						}
						else if(juge2 == 'n')
							break;
						else{
							cout << "是否继续(y/n)\n";
							cin >> juge2;
						}
					}
				}
				else
					cout << "未创建链表，请先创建链表\n";	
				break;
			//插入图书	
			case 3:										
				if(List->next){
					int loc;
					cout << "请输入想要插入的位置:";
					cin >> loc;
					if(cin){
						int flag = InsertList(List,loc);
						if(flag)
							cout << "插入成功\n";
						else
							cout << "插入失败\n";
					}
					else{
						cin.clear();
						cin.sync();		//清空流   
						cout << "插入位置格式错误\n";	
					}
				}
				else
					cout << "未创建链表，请先创建链表\n";   			
				break;
			//删除图书   
			case 4:   										 	
				if(List->next){
					cout << "请输入你想要删除的图书的ISBN：";
					cin >> isbn; 
					int flag = DeleteList(List,isbn);
					if(flag)
						cout << "删除成功\n";
					else
						cout << "删除失败\n";
				}
				else
					cout << "未创建链表，请先创建链表\n";											
				break;
			//修改图书信息 
			case 5:    										
				if(List->next){
					int flag;
					cout << "你想修改的图书的ISBN:";
					cin >> isbn;
					flag = ChangeList(List,isbn);
					if(flag)
						cout << "修改成功\n";
					else
						cout << "修改失败\n";
				}
				else
					cout << "未创建链表，请先创建链表\n";	
				break;
			//打印图书信息  
			case 6: 							
				if(List->next){
					PrintList(List);	
				}
				else
					cout << "未创建链表，请先创建链表\n";								 
				break;	
			//退出程序
			case 0:     										
				exit(0); 
				break;
			default:
				cout << "请输入正确的操作序号！\n";
		}
		system("pause");
		system("cls");
		menu();
		cout << "请选择对应的功能选项进行相应操作：\n";
		cin >> choice;
	}
	return 0;
}
