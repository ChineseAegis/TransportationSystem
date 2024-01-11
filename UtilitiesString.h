/* 
 * UtilitiesString.h
 * 产生随机整数、随机整数数组和随机字符串数组
 * @作者 郭艳<guoyan49@cug.edu.cn>
 * @author Yan Guo<guoyan49@cug.edu.cn> 2023-12-9
 * 2024-01-05 增加创建一个值不重复的长度为n的随机字符串数组
 */
#pragma once

#include <string>
#include <stdlib.h> //atoi
using std::string;

//裁剪字符串前后的空格
static string trim_blank_space(const string& str) {
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos) {  //若找不到空格  string::npos是一个常数，表示size_t的最大值，用于表示不存在的位置。
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
		return str.substr(pos, pos2 - pos + 1); //子串：第一个非空格作为起始位置
	// 字符个数：pos2-pos+1
	return str.substr(pos);
}
//————————————————
//版权声明：本文为CSDN博主「MangoGZH 」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https ://blog.csdn.net/weixin_43793960/article/details/106193050


//对字符串前后空格裁剪
static string stringfunction(char* str) {
	return trim_blank_space(str);// string(str);
}

//将字符串转换为整数然后转换为bool值。
static bool boolfunction(char* str) {
	return bool(std::atoi(str));
}

//将字符串转换为整数。
static int intfunction(char* str) {
	return std::atoi(str);
}