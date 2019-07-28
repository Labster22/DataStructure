#include<iostream>
#include <cstring>
#include <cmath>

using namespace std;

//Open_file类，打开文件 
class Open_file{
	public:
		Open_file();
		
	protected:
		char word[500];
		int n;
};

//Find类，查找单词,继承Open_file类 
class Find:public Open_file{
	public:
		Find(string f_word);
		void findWord();
		void dispay();
		
	protected:
		char fword[50];			//储存f_word
		char part_word[50];		//word里的一个单词
		int position[50];		//所查找的单词的位置
		int num[1];				//储存k_judge的大小
		int pword_size;
		int fword_length;
};

//Replace类,替换单词,继承Find类 
class Replace:public Find{
	public:
		Replace(string f_word):Find(f_word){
			cout << "你想替换成什么单词:\n";
			cin >> r_word;
			memset(rword,0,sizeof(rword));
			strcpy(rword,r_word.c_str());//将指定的单词转换为数组
			rword_length = strlen(rword);

			memset(new_word,0,sizeof(new_word));
			cha = fabs(rword_length-fword_length);
		}
		void replaceWord();
		
	private:
		string r_word;
		char rword[50];
		char new_word[500];
		int rword_length;
		int cha;//计算字母的差值
};

//Del类,删除单词,继承Find类 
class Del:public Find{
	public:
		Del(string f_word):Find(f_word){
			memset(new_word,0,sizeof(new_word));
		}
		void delWord();
		
	private:
		char new_word[500];
};
