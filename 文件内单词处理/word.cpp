#include<iostream>
#include <fstream>
#include"word.h"
using namespace std;

//Open_file的构造函数 
Open_file::Open_file(){
	memset(word,0,sizeof(word));//将数组置空
	ifstream file;
	file.open("target.txt");
	if(!file){//判断文件是否打开
		cout << "打开target.txt失败!\n";
		exit(0);
	}
	else{
		ifstream fin("target.txt");
		fin >> noskipws;//读入空格
		for(int i=0;i<500;i++){
			fin >> word[i];//将文件内容读入数组中
		}
	}
	n = strlen(word);
	file.close();
}

//Find的构造函数 
Find::Find(string f_word){
	memset(position,0,sizeof(position));
	memset(part_word,0,sizeof(part_word));
	memset(num,0,sizeof(num));
	memset(fword,0,sizeof(fword));
	
	strcpy(fword,f_word.c_str());//将字符串转化为字符数组
	fword_length = strlen(fword);
	findWord();
}

//查找单词 
void Find::findWord(){
	int k = 0,number = 0;
	int i = 0,j = 0;
	int judge;//判断是否相等
	for(i;i < n;){
		if(word[i] < 65 || (word[i] > 90 && word[i] < 97) || word[i] > 122)//除去单词前不是单词部分
			i++;
		else{
			part_word[j] = word[i];
			j++;
			i++;
			if(word[i] < 65 || (word[i] > 90 && word[i] < 97) || word[i] > 122){//一个单词结束
				judge = strcmp(part_word,fword);//判断单词是否相等
				pword_size = strlen(part_word);//计算分离出来的单词大小
				if(judge == 0){
					if(k < n){
						position[k]=i-pword_size;
						k++;
					}
					number++;
					num[0] = number;
				}
				if(num[0] == 0)
					position[k] = -1;
				j = 0;
				memset(part_word,0,sizeof(part_word));//再次将part_word数组置空，放置前面长单词将后面单词覆盖
				continue;
			}
		}
	}
}

//显示查找结果 
void Find::dispay(){
	if(num[0] == 0)
		cout << "文件内没有这个单词!\n"<<endl;
	else{
			cout << "所有出现的位置:";
			for(int i = 0;i < num[0];i++)
			 	cout << position[i]+1 << " ";
			cout << endl << fword << " 在此文件内出现 " << num[0] << " 次\n";
		}
}

//替换单词 
void Replace::replaceWord(){
	int i = 0,j = 0,m = 0,k;
	int judge = 0;
	for(i;i < n;){
		if(i == position[m]){
			judge++;
			for(k = 0;k < rword_length;k++){
				new_word[j] = rword[k];
				i++;
				j++;
			}
			m++;//找到下一个相同单词的首位置
			if(rword_length < fword_length)
				i += cha;
			else
				i -= cha;
		}
		new_word[j] = word[i];
		i++;
		j++;
	}
	if(judge == 0)
		cout << "文件内没有你想替换的单词！\n";
	else{
			ofstream fout("target.txt");//将数组写入到文件内
			for(int j = 0;j < n;j++)
				fout << new_word[j];
			cout << endl << "替换了" << num[0] << "个单词\n";
		}
}

//删除单词 
void Del::delWord(){
	int i = 0,j = 0,m = 0,k = 0;
	int judge = 0;
	for(i;i < n;){
		if(i == position[m]){
			judge++;
			m++;//找到下一个相同单词的首位置
			i += fword_length;
		}
		new_word[j] = word[i];
		i++;
		j++;
	}
	if(0 == judge)
		cout<<"文件内没有你想删除的单词！\n";
	else{
		ofstream fout("target.txt");//将数组写入到文件内
		for(int j = 0;j<n;j++)
			fout<<new_word[j];
		cout << endl << "删除了" << num[0] << "个单词\n";
	}
}
