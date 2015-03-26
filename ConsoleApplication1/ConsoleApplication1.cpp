// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <map>
#include <list>
#include <string>
#include <iostream>

#include <atltime.h>
#include <minwinbase.h>

void getTradeDate();

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	map<long, list<string>> m1;
	m1[1].push_back("aa");
	map<long, list<string>>::iterator it;
	for (it = m1.begin(); it != m1.end(); it++)
	{
		cout << it->first << " | ";
		cout << it->second.size()<<endl;
	}
	cout << "map--end" << endl;

	//getTradeDate();

	//tchar
	TCHAR tc = '1';


	return 0;
}

void getTradeDate()
{
	/*
	time_t time_t1;
	time(&time_t1);

	struct tm st_tm;
	localtime_s(&st_tm, &time_t1);
	*/


	/*
	SYSTEMTIME st;
	GetLocalTime(&st);
	*/

	//CTime  ct = CTime::GetCurrentTime();
	//int year = ct.GetYear();
	//int month = ct.GetMonth();
	//int day = ct.GetDay();
	//int dayofweek = ct.GetDayOfWeek();//7为星期六，1为星期天，2为星期一

	//求一般性的上一个交易日，周一、周日、周六、都对应上周五
	int year = 2015;
	int month = 3;
	int day = 23;
	int dayofweek = 2;


	int std_day[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//非闰年每月份的天数

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		std_day[2] += 1;//表示如果是闰年,二月份为29天

	int gap = 0;
	if (dayofweek == 7 || dayofweek == 1 || dayofweek == 2)
	{
		gap = (dayofweek % 7) + 1;
	}

	int z_year, z_month, z_day;
	int tmp_z_day = day - gap;
	if (tmp_z_day > 0)
	{
		z_year = year;
		z_month = month;
		z_day = day - 1;
	}
	else
	{
		if (month == 1)
		{
			z_year = year - 1;
			z_month = 12;
			z_day = std_day[12] + tmp_z_day;
		}
		else
		{
			z_year = year;
			z_month = month - 1;
			z_day = std_day[month - 1] + tmp_z_day;
		}

	}



	//if (dayofweek == 7) //day-1
	//{
	//	if (day == 1)
	//	{
	//		if (month == 1) //year-1,12,31
	//		{
	//			z_year = year - 1;
	//			z_month = 12;
	//			z_day = std_day[12];
	//		}
	//		else //month-1
	//		{
	//			z_year = year;
	//			z_month = month - 1;
	//			z_day = std_day[month - 1];
	//		}
	//		
	//	}
	//	else //day-1
	//	{
	//		z_year = year;
	//		z_month = month;
	//		z_day = day - 1;
	//	}
	//} 
	//else if(dayofweek == 1) //day-2
	//{
	//	if (day == 2)
	//	{
	//		if (month == 1)
	//		{

	//		} 
	//		else
	//		{
	//		}
	//	} 
	//	else
	//	{
	//	}
	//}
	//else if (dayofweek == 2) //day-3
	//{

	//}
	//else
	//{

	//}
}
