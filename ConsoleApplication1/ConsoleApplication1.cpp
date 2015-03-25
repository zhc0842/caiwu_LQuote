// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <map>
#include <list>
#include <string>
#include <iostream>

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


	return 0;
}

