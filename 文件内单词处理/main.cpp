#include <iostream>
#include "word.h"

using namespace std;

void menu(){
	cout << " -----------------------------------------------------------------------------\n"
	     << "\n"
	     << "                		1: ����ָ����ĳ������\n"
	     << "                		2: �滻ָ��ĳ������\n"
	     << "                		3: ɾ��ָ��ĳ������\n"
	     << "                		0: ��������\n"
	     << "\n"
	     << " -----------------------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
	int choice;
	Open_file start;
	string f_word;		//��Ҫ���ҵĵ��� 
	string d_word;		//��Ҫɾ���ĵ��� 
	while(1){
		menu(); 
		cout << "����������ʵ�ֵ���Ŀ�����:\n"; 
		cin >> choice;
		switch(choice){
			//���ҵ��� 
			case 1:{
				cout << "����������Ҫ���ҵĵ���:\n";
				cin >> f_word;
				Find find(f_word);
				find.dispay();
				break;
			}
			//�滻���� 
			case 2:{
				cout << "����������Ҫ�滻�ĵ���:\n";
				cin >> f_word;
				Replace replace(f_word);
				replace.replaceWord();
				break;
			}
			//ɾ������		
			case 3:{
				cout << "����������Ҫɾ���ĵ���:\n";
				cin >> d_word;
				Del del(d_word);
				del.delWord();
				break;
			}
			
			case 0:
				exit(0);
			
			default:
				cout << "��������ȷ�Ĳ�����ţ�\n";
				break;
		}
		system("pause");		//��ͣ
        system("cls");			//���� 
	}
	return 0;
}

		
