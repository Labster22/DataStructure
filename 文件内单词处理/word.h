#include<iostream>
#include <cstring>
#include <cmath>

using namespace std;

//Open_file�࣬���ļ� 
class Open_file{
	public:
		Open_file();
		
	protected:
		char word[500];
		int n;
};

//Find�࣬���ҵ���,�̳�Open_file�� 
class Find:public Open_file{
	public:
		Find(string f_word);
		void findWord();
		void dispay();
		
	protected:
		char fword[50];			//����f_word
		char part_word[50];		//word���һ������
		int position[50];		//�����ҵĵ��ʵ�λ��
		int num[1];				//����k_judge�Ĵ�С
		int pword_size;
		int fword_length;
};

//Replace��,�滻����,�̳�Find�� 
class Replace:public Find{
	public:
		Replace(string f_word):Find(f_word){
			cout << "�����滻��ʲô����:\n";
			cin >> r_word;
			memset(rword,0,sizeof(rword));
			strcpy(rword,r_word.c_str());//��ָ���ĵ���ת��Ϊ����
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
		int cha;//������ĸ�Ĳ�ֵ
};

//Del��,ɾ������,�̳�Find�� 
class Del:public Find{
	public:
		Del(string f_word):Find(f_word){
			memset(new_word,0,sizeof(new_word));
		}
		void delWord();
		
	private:
		char new_word[500];
};
