#include<iostream>
#include <sys/time.h>
using namespace std;
class TDate
{
public:
	void SetDate(int y, int m, int d);
	int IsLeapYear();
	void SetTime(int h, int m, int s);
	void DisplayTime();
private:
	int year, month, day;
	int hh, min, sec;
	time_t timep;

	/*tm结构在time.h中的定义：
	struct tm {
		int tm_sec;  		//秒–取值区间为[0,59]
		int tm_min;  		//分 - 取值区间为[0,59]
		int tm_hour;  		//时 - 取值区间为[0,23]
		int tm_mday; 		//一个月中的日期 - 取值区间为[1,31]
		int tm_mon; 		//月份（从一月开始，0代表一月） - 取值区间为[0,11]
		int tm_year; 		//年份，其值从1900开始
		int tm_wday; 		//星期–取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推
		int tm_yday; 		//从每年的1月1日开始的天数–取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推
		int tm_isdst; 		//夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0；不了解情况时，tm_isdst()为负。
		long int tm_gmtoff; //指定了日期变更线东面时区中UTC东部时区正秒数或UTC西部时区的负秒数
		const char *tm_zone;//当前时区的名字(与环境变量TZ有关)
	};*/
	struct tm *p_tm;


	/*头文件： <sys/time.h>；timeval结构的用于指定时间值
	struct timeval
	{
		time_t tv_sec; 		//秒 [long int]
		suseconds_t tv_usec;//微秒 [long int]
	};*/
	struct timeval time_tv;
};
void TDate::SetDate(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;

	/*time() 函数返回自 Unix 纪元（January 1 1970 00:00:00 GMT）起的当前时间的秒数。[1]
	主要用来获取当前的系统时间，返回的结果是一个time_t类型，
	其值表示从UTC（Coordinated Universal Time）时间1970年1月1日00:00:00（称为UNIX系统的Epoch时间）
	到当前时刻的秒数。然后调用localtime函数将time_t所表示的UTC时间转换为本地时间（我们是+8区，比UTC多8个小时）
	并转成struct tm类型，该类型的各数据成员分别表示年月日时分秒。*/

	timep = time(NULL);
	p_tm = localtime(&timep);
	p_tm->tm_year = y - 1900;
	p_tm->tm_mon = m - 1;
	p_tm->tm_mday = d;

	/*mktime()用来将参数p_tm所指的tm结构数据转换成从公元1970年1月1日0时0分0 秒算起至今的UTC时间所经过的秒数*/
	timep = mktime(p_tm);

	time_tv.tv_sec = timep;
	time_tv.tv_usec = 0;

	/*
	头文件：#include<sys/time.h>
	函数原型：int settimeofday ( const struct timeval *tv,const struct timezone *tz);
	settimeofday（）会把目前时间设成由tv所指的结构信息，当地时区信息则设成tz所指的结构。
	其参数tv是保存设置时间结果的结构体，参数tz用于保存时区结果
	注意，只有root权限才能使用此函数修改时间。成功则返回0，失败返回－1，错误代码存于errno。
	EPERM 并非由root权限调用settimeofday（），权限不够。
	EINVAL 时区或某个数据是不正确的，无法正确设置时间。
	如果tv或tz某一项为NULL，表示对相关的信息不感兴趣。*/
	settimeofday(&time_tv, NULL);

}
void TDate::SetTime(int h, int m, int s)
{
	hh = h;
	min = m;
	sec = s;

	timep = time(NULL);
	p_tm = localtime(&timep);
	p_tm->tm_hour = h;
	p_tm->tm_min = m;
	p_tm->tm_sec = s;

	//timep = time(NULL);
	timep = mktime(p_tm);

	time_tv.tv_sec = timep;
	time_tv.tv_usec = 0;
	settimeofday(&time_tv, NULL);
}
int TDate::IsLeapYear()
{
	return(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
void TDate::DisplayTime()
{
	timep = time(NULL);
	p_tm = localtime(&timep);
	cout << p_tm->tm_year + 1900 << " year 年";
	cout << p_tm->tm_mon + 1 << "month 月";
	cout << p_tm->tm_mday << " date 日";
	cout << " " << "week 星期" << p_tm->tm_wday;
	cout << " " << p_tm->tm_hour << ":" << p_tm->tm_min << ":" << p_tm->tm_sec;
	if (TDate::IsLeapYear()) cout << " lunar 润年";
	cout << endl;
}
