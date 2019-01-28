#pragma once
#include <ctime>
#include <string>
using namespace std;
class MyTime
{
public:
	MyTime();
	virtual ~MyTime();
	int getYear(tm input);
	int getMonth(tm input);
	int getDate(tm input);
	int getWeekDay(tm input);
	tm getCurrentTm();
	int getHour(tm input);
	int getMin(tm input);
	int getSec(tm input);
	void printTime(tm input);
};




