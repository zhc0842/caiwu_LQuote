void write_TradeDates()
{
map<string, string> month_days_map = Load_Configuration("2015.csv");//格式为01=0000111110011111001111100111110
ofstream fout("2015.txt");//格式为20150310
map<string, string>::iterator it;
for (it = month_days_map.begin(); it != month_days_map.end(); it++)
{
	string days = it->second;
	for (unsigned int i = 0; i < days.size(); i++)
	{
		if (days.at(i) == '1')
		{
			fout << "2015";
			fout << (it->first).c_str();

			int d = i + 1;
			if (d<10)
			{
				fout << "0";
			}
			char aa[10];
			_itoa_s(d, aa, 10);
			fout << aa << endl;
		}	
	}
}
fout.close();
}
map<string, string> Load_Configuration(char* cfgFilePath)
{
	if (cfgFilePath == NULL)
	{
		cfgFilePath = "caiwu.cfg";
	}
	ifstream cfgFin;
	cfgFin.open(cfgFilePath);
	/*
	if (!cfgFin.is_open())
	{
		AfxMessageBox(_T("can not open caiwu.cfg ! program will exit!"), MB_OK);
		exit(0);
	}
	*/
	int lines = 0;
	map<string, string> cfg_map;
	while (!cfgFin.eof())
	{
		char line[256];
		cfgFin.getline(line, sizeof(line));
		string s = line;
		int i = s.find("=");
		//空白行,#,不包含=或第1个为=，跳过  
		if (s.empty() || s[0] == '#' || i <= 0)
		{
			continue;
		}
		string str_key = s.substr(0, i);
		string str_val = s.substr(i + 1);

		cfg_map[str_key] = str_val;
	}
	cfgFin.close();
	return cfg_map;
}