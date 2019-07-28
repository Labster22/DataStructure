#include<iostream>
#include <fstream>
#include"word.h"
using namespace std;

//Open_file�Ĺ��캯�� 
Open_file::Open_file(){
	memset(word,0,sizeof(word));//�������ÿ�
	ifstream file;
	file.open("target.txt");
	if(!file){//�ж��ļ��Ƿ��
		cout << "��target.txtʧ��!\n";
		exit(0);
	}
	else{
		ifstream fin("target.txt");
		fin >> noskipws;//����ո�
		for(int i=0;i<500;i++){
			fin >> word[i];//���ļ����ݶ���������
		}
	}
	n = strlen(word);
	file.close();
}

//Find�Ĺ��캯�� 
Find::Find(string f_word){
	memset(position,0,sizeof(position));
	memset(part_word,0,sizeof(part_word));
	memset(num,0,sizeof(num));
	memset(fword,0,sizeof(fword));
	
	strcpy(fword,f_word.c_str());//���ַ���ת��Ϊ�ַ�����
	fword_length = strlen(fword);
	findWord();
}

//���ҵ��� 
void Find::findWord(){
	int k = 0,number = 0;
	int i = 0,j = 0;
	int judge;//�ж��Ƿ����
	for(i;i < n;){
		if(word[i] < 65 || (word[i] > 90 && word[i] < 97) || word[i] > 122)//��ȥ����ǰ���ǵ��ʲ���
			i++;
		else{
			part_word[j] = word[i];
			j++;
			i++;
			if(word[i] < 65 || (word[i] > 90 && word[i] < 97) || word[i] > 122){//һ�����ʽ���
				judge = strcmp(part_word,fword);//�жϵ����Ƿ����
				pword_size = strlen(part_word);//�����������ĵ��ʴ�С
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
				memset(part_word,0,sizeof(part_word));//�ٴν�part_word�����ÿգ�����ǰ�泤���ʽ����浥�ʸ���
				continue;
			}
		}
	}
}

//��ʾ���ҽ�� 
void Find::dispay(){
	if(num[0] == 0)
		cout << "�ļ���û���������!\n"<<endl;
	else{
			cout << "���г��ֵ�λ��:";
			for(int i = 0;i < num[0];i++)
			 	cout << position[i]+1 << " ";
			cout << endl << fword << " �ڴ��ļ��ڳ��� " << num[0] << " ��\n";
		}
}

//�滻���� 
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
			m++;//�ҵ���һ����ͬ���ʵ���λ��
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
		cout << "�ļ���û�������滻�ĵ��ʣ�\n";
	else{
			ofstream fout("target.txt");//������д�뵽�ļ���
			for(int j = 0;j < n;j++)
				fout << new_word[j];
			cout << endl << "�滻��" << num[0] << "������\n";
		}
}

//ɾ������ 
void Del::delWord(){
	int i = 0,j = 0,m = 0,k = 0;
	int judge = 0;
	for(i;i < n;){
		if(i == position[m]){
			judge++;
			m++;//�ҵ���һ����ͬ���ʵ���λ��
			i += fword_length;
		}
		new_word[j] = word[i];
		i++;
		j++;
	}
	if(0 == judge)
		cout<<"�ļ���û������ɾ���ĵ��ʣ�\n";
	else{
		ofstream fout("target.txt");//������д�뵽�ļ���
		for(int j = 0;j<n;j++)
			fout<<new_word[j];
		cout << endl << "ɾ����" << num[0] << "������\n";
	}
}
