#include<iostream>

using namespace std;

//�洢�ṹ��
typedef struct LNode{
	string isbn;		//ͼ���ISBN�� 
	string name;		//���� 
	double price;		//�۸� 
	struct LNode *next;
}LNode,*LinkList;
 
//�˵�
void menu(){
	cout << "			        ͼ�����ϵͳ\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "				1 ��������\n";
	cout << "				2 ����ͼ��ISBN����ͼ��\n";
	cout << "				3 ����ͼ��\n";
	cout << "				4 ����ISBNɾ��ͼ��\n";
	cout << "				5 �޸�ͼ����Ϣ\n";
	cout << "				6 ��ӡ����ͼ��\n";
	cout << "				0 �˳�����\n";
	cout << "-------------------------------------------------------------------------------\n";
}

//��ʼ��
int InitList(LinkList &List){
	List = new LNode;				//�����µ�ͷ��� 
	List->next = NULL;				//ͷ����ָ����Ϊ�� 
	return 1;
} 

//��������
void CreateList(LinkList &List){
	LinkList new_node,rear;
	rear = List;                    		//����β�ڵ� 
	char juge = 'y';                    	//�ж��Ƿ�������� 
	while(juge == 'y'){
			cout << "������ͼ���ISBN�����ֺͼ۸�\n";
			new_node = new LNode;									//ÿ�����������µĽڵ�ռ� 
			cin >> new_node->isbn >> new_node->name >> new_node->price;
			if(cin){
				new_node->next = NULL;									//���½��ڵ��ָ������Ϊ�� 
				rear->next = new_node;									//�����½��Ľڵ�
				rear = new_node;										//����ָ��β�ڵ� 
				cout << "�Ƿ��������(y or n)?\n";
				cin >> juge;
			}
			else{
				cin.clear();
				cin.sync();			//�����   
				cout << "��ʽ����, ��������\n";	
			}
	}
}

//��ӡ����ͼ����Ϣ 
void PrintList(LinkList List){
	LinkList print;     		//printָ����Ҫ��ӡ�Ľ�� 
	print = List->next;
	while(print){
		cout << print->isbn << " " << print->name << " " << print->price << endl;
		print = print->next;
	}
}

//����ͼ�� 
void SearchList(LinkList &List,string isbn,string name){
	LinkList sear; 
	sear = List->next;
	cout << "����ISBN:"; 
	cin >> isbn;
	while(sear && sear->isbn != isbn)
		sear = sear->next; 
	if(!sear)
		cout << "ͼ�鲻����\n";
	else
		cout << sear->isbn << " " << sear->name << " " << sear->price << endl;
}

//����ͼ��
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
	cout << "����ͼ���ISBN�������ͼ۸�\n";
	cin >> new_node->isbn >> new_node->name >> new_node->price;
	new_node->next = inser->next;
	inser->next = new_node;
	return 1;
} 

//ɾ��ͼ�� 
int DeleteList(LinkList &List,string isbn){
	LinkList del = List,pre;   //pre����Ҫɾ���ڵ��ǰһ�� 
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

//�޸�ͼ����Ϣ 
int ChangeList(LinkList &List,string isbn){
	LinkList alter; 
	alter = List;
	while(alter && alter->isbn != isbn){
		alter = alter->next;
	}
	if(!alter)
		return 0;
	cout << "�޸�ͼ���isbn�����ֺͼ۸�Ϊ��";
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
		cin.sync();		//�����  
		cout << "��ʽ����,";
		return 0; 
	}
}


int main(){
	LinkList List;
	InitList(List);
	int choice;
	string name = "0",isbn = "0",price = "0";   //����Ҫͼ�����Ϣ��ʼ��
	menu();
	cout << "\n��ѡ���Ӧ�Ĺ���ѡ�������Ӧ������\n";              
	cin >> choice;
	while(1){
		switch(choice){
			 //��������
			case 1:
				if(List->next != NULL){                        //ͷ���ָ����Ϊ�ռ�Ϊ�ѳ�ʼ���� 
					cout << "˳����Ѿ���ʼ�����ٴγ�ʼ�������ԭ�����ݡ��Ƿ����  (y/n):";
					char juge1;
					cin >> juge1;
					while(1){
						if(juge1 == 'y'){
							CreateList(List);								 //���´�������
							break; 
						}
						else if(juge1 == 'n'){
							break;
						}
						else{
							cout << "�Ƿ����  (y/n):";					//�����y��n֮������Ľ������			      
							cin >> juge1;
						}
					}
				}
				else{
					CreateList(List);										
					break;
				}
				break;	
			//����ͼ�� 	
			case 2: 												 
				if(List->next){
					char juge2 = 'y';
					while(1){
						if(juge2 == 'y'){
							SearchList(List,isbn,name);											
							cout << "�Ƿ������ѯ��(y/n)\n";
							cin >> juge2;
						}
						else if(juge2 == 'n')
							break;
						else{
							cout << "�Ƿ����(y/n)\n";
							cin >> juge2;
						}
					}
				}
				else
					cout << "δ�����������ȴ�������\n";	
				break;
			//����ͼ��	
			case 3:										
				if(List->next){
					int loc;
					cout << "��������Ҫ�����λ��:";
					cin >> loc;
					if(cin){
						int flag = InsertList(List,loc);
						if(flag)
							cout << "����ɹ�\n";
						else
							cout << "����ʧ��\n";
					}
					else{
						cin.clear();
						cin.sync();		//�����   
						cout << "����λ�ø�ʽ����\n";	
					}
				}
				else
					cout << "δ�����������ȴ�������\n";   			
				break;
			//ɾ��ͼ��   
			case 4:   										 	
				if(List->next){
					cout << "����������Ҫɾ����ͼ���ISBN��";
					cin >> isbn; 
					int flag = DeleteList(List,isbn);
					if(flag)
						cout << "ɾ���ɹ�\n";
					else
						cout << "ɾ��ʧ��\n";
				}
				else
					cout << "δ�����������ȴ�������\n";											
				break;
			//�޸�ͼ����Ϣ 
			case 5:    										
				if(List->next){
					int flag;
					cout << "�����޸ĵ�ͼ���ISBN:";
					cin >> isbn;
					flag = ChangeList(List,isbn);
					if(flag)
						cout << "�޸ĳɹ�\n";
					else
						cout << "�޸�ʧ��\n";
				}
				else
					cout << "δ�����������ȴ�������\n";	
				break;
			//��ӡͼ����Ϣ  
			case 6: 							
				if(List->next){
					PrintList(List);	
				}
				else
					cout << "δ�����������ȴ�������\n";								 
				break;	
			//�˳�����
			case 0:     										
				exit(0); 
				break;
			default:
				cout << "��������ȷ�Ĳ�����ţ�\n";
		}
		system("pause");
		system("cls");
		menu();
		cout << "��ѡ���Ӧ�Ĺ���ѡ�������Ӧ������\n";
		cin >> choice;
	}
	return 0;
}
