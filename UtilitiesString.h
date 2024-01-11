/* 
 * UtilitiesString.h
 * �����������������������������ַ�������
 * @���� ����<guoyan49@cug.edu.cn>
 * @author Yan Guo<guoyan49@cug.edu.cn> 2023-12-9
 * 2024-01-05 ���Ӵ���һ��ֵ���ظ��ĳ���Ϊn������ַ�������
 */
#pragma once

#include <string>
#include <stdlib.h> //atoi
using std::string;

//�ü��ַ���ǰ��Ŀո�
static string trim_blank_space(const string& str) {
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos) {  //���Ҳ����ո�  string::npos��һ����������ʾsize_t�����ֵ�����ڱ�ʾ�����ڵ�λ�á�
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
		return str.substr(pos, pos2 - pos + 1); //�Ӵ�����һ���ǿո���Ϊ��ʼλ��
	// �ַ�������pos2-pos+1
	return str.substr(pos);
}
//��������������������������������
//��Ȩ����������ΪCSDN������MangoGZH ����ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/weixin_43793960/article/details/106193050


//���ַ���ǰ��ո�ü�
static string stringfunction(char* str) {
	return trim_blank_space(str);// string(str);
}

//���ַ���ת��Ϊ����Ȼ��ת��Ϊboolֵ��
static bool boolfunction(char* str) {
	return bool(std::atoi(str));
}

//���ַ���ת��Ϊ������
static int intfunction(char* str) {
	return std::atoi(str);
}