#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class clFile
{
public:
	static void SaveNewLineInFile(const string &FileName,const string& Line)
	{
		ofstream File(FileName, ios::app);

		if (File.is_open())
		{
			File << Line << "\n";

			File.close();
		}
	}
};