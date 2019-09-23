#include <iostream>
#include "word.h"

using namespace std;

void menu(){
	cout << " -----------------------------------------------------------------------------\n"
	     << "\n"
	     << "                		1: 查找指定的某个单词\n"
	     << "                		2: 替换指定某个单词\n"
	     << "                		3: 删除指定某个单词\n"
	     << "                		0: 结束操作\n"
	     << "\n"
	     << " -----------------------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
	int choice;
	Open_file start;
	string f_word;		//需要查找的单词 
	string d_word;		//需要删除的单词 
	while(1){
		menu(); 
		cout << "请输入你想实现的项目的序号:\n"; 
		cin >> choice;
		switch(choice){
			//查找单词 
			case 1:{
				cout << "请输入你想要查找的单词:\n";
				cin >> f_word;
				Find find(f_word);
				find.dispay();
				break;
			}
			//替换单词 
			case 2:{
				cout << "请输入你想要替换的单词:\n";
				cin >> f_word;
				Replace replace(f_word);
				replace.replaceWord();
				break;
			}
			//删除单词		
			case 3:{
				cout << "请输入你想要删除的单词:\n";
				cin >> d_word;
				Del del(d_word);
				del.delWord();
				break;
			}
			
			case 0:
				exit(0);
			
			default:
				cout << "请输入正确的操作序号！\n";
				break;
		}
		system("pause");		//暂停
        system("cls");			//清屏 
	}
	return 0;
}

		
