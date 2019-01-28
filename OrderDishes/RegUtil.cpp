#include "RegUtil.h"
#include "StringUtils.h"
#include <regex.h>
#include <string.h>
#include "StringUtils.h"
#include <cstdlib>
#include <iostream>
using namespace std;
RegUtil::RegUtil()
{
}


RegUtil::~RegUtil()
{
}

bool RegUtil::isValid(char *str, char *patterm)
{
	char ebuff[256];
	regex_t reg;
	int cflag = REG_EXTENDED | REG_NEWLINE | REG_NOSUB;
	int status = 0;
	status = regcomp(&reg, patterm, cflag);

	if (status != 0) {
		regerror(status, &reg, ebuff, 256);
		cout << ebuff << endl;
		return false;
	}
	status = regexec(&reg, str, 0, NULL, 0);
	if (status == 0) {
		return true;
	}
	else {
		return false;
	}
}


bool RegUtil::isPositiveInt(char *str)
{
	char *patterm = "^[+]?[0-9]+$";
	return isValid(str, patterm);
}

bool RegUtil::isPositiveInt(string str) {
	return isPositiveInt(StringUtils::stringToChar(str));
}

bool RegUtil::isPositiveDouble(char *str)
{
	char *patterm = "^[+]?[0-9]+[.]?[0-9]+$";
	return isValid(str, patterm);
}

bool RegUtil::isPositiveDouble(string str) {
	return isPositiveDouble(StringUtils::stringToChar(str));
}

int RegUtil::returnIntIfValid(string input,int minNum,int maxNum)
{
	if (isPositiveInt(input))
	{
		int choice;
		choice = atoi(input.c_str());
		if (choice == 0) {
			cout << "Choice should not be 0 请输入不为零的整数！" << endl;
			return 0;
		}
		if (choice >maxNum && maxNum!=-1) {
			cout << "invalid number 输入的数字不合法！" << endl;
			return 0;
		}
		if (choice < minNum && minNum != -1) {
			cout << "invalid number 输入的数字不合法！" << endl;
			return 0;
		}

		return choice;
	}
	else
	{
		cout << "Choice should be an Integer biigger than 0请输入大于0整数！" << endl;
		return 0;
	}
};


double RegUtil::returnDoubleIfValid(string num, double minNum, double maxNum)
{
	string temp;
	if (num.at(0) == '-') {
		temp = num.substr(1, num.length());
	}
	else {
		temp = num;
	}
	bool validDouble = isPositiveDouble(temp);
	double result;
	if (validDouble) 
	{
		result= StringUtils::stringToDouble(num);
		if (result ==0) {
			cout << "can not be zero 不可为零！" << endl;
			return 0;
		}
		if (result > maxNum&&maxNum != -1) {
			cout << "bigger than maxNum allowed 输入的数字超过最大值" << endl;
			return 0;
		}
		if (result < minNum&&minNum != -1) {
			cout << "smaller than minNum allowed 输入的数字小于最小值" << endl;
			return 0;
		}
		return result;
	}
	else 
	{
		cout<<"illegal input 输入的字符不合法"<<endl;
		return 0;
	}
};