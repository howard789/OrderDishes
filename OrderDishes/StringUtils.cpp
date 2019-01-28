#include "StringUtils.h"
#include <string>
using namespace std;

StringUtils::StringUtils()
{
}


StringUtils::~StringUtils()
{
}

char *StringUtils::stringToChar(string str) {
	char *p = new char[str.length()];
	for (int i = 0; i < str.length(); i++) {
		p[i] = str[i];
	}
	p[str.length()] = '\0';
	return p;
}



double StringUtils::stringToDouble(string num)
{
	bool minus = false;       
	string real = num;       
	if (num.at(0) == '-')
	{
		minus = true;
		real = num.substr(1, num.size() - 1);
	}

	char c;
	int i = 0;
	double result = 0.0, dec = 10.0;
	bool isDec = false;       //is decimal
	unsigned long size = real.size();
	while (i < size)
	{
		c = real.at(i);
		if (c == '.')
		{//contain decimal
			isDec = true;
			i++;
			continue;
		}
		if (!isDec)
		{
			result = result * 10 + c - '0';
		}
		else
		{//decimal
			result = result + (c - '0') / dec;
			dec *= 10;
		}
		i++;
	}

	if (minus == true) {
		result = -result;
	}

	return result;
}


