#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clUser.h"
#include "clString.h"
#include "clScreen.h"
#include "clUtil.h"
using namespace std;

class clLoginLogListScreen : protected clScreen
{
private:
	static void _PrinHeader()
	{
		cout <<"\t\t\t_____________________________________________________________________________________\n\n";
		cout << left;
		cout << "\t\t\t| " << setw(32) << "Date - Time";
		cout << "| " << setw(20) << "Username";
		cout << "| " << setw(12) << "Password";
		cout << "| " << setw(12) << "Permissions"<<"|\n";
		cout << "\t\t\t_____________________________________________________________________________________\n\n";
	}
	static void _PrintRecordLine(const clUser::stLoginLog& Record)
	{
		cout<< "\t\t\t| " << setw(32) << Record.Date;
		cout << "| " << setw(20) << Record.Username;
		cout << "| " << setw(12) << Record.Password;
		cout << "| " << setw(12) << Record.Permissions << "|\n";
	}
	static void _PrintList(const vector <clUser::stLoginLog>& veRecords)
	{
		for (const clUser::stLoginLog& Record : veRecords)
		{
			_PrintRecordLine(Record);
		}
		cout<< "\t\t\t_____________________________________________________________________________________\n\n";
	}
public:
	static void ShowLoginLogListScreen()
	{
		vector <clUser::stLoginLog> veRecords = clUser::GetLoginLogList();

		DrawScreenHeader(clUtil::Spaces(8) + "Login Log List Screen", clUtil::Spaces(13) +  to_string(veRecords.size())  + " Record(s)");

		_PrinHeader();
		_PrintList(veRecords);
	}
};