#pragma once
#include <iostream>
#include "clScreen.h"
#include "clClient.h"
#include "clUtil.h"
using namespace std;

class clTransferLogScreen : protected clScreen
{
private:
	static void _PrintHeader()
	{
		cout << "\t_________________________________________________________________________________________________________________________\n\n";
		cout << left;
		cout << "\t| " << setw(30) << "Date - Time";
		cout << "| " << setw(8) << "S.Acc";
		cout << "| " << setw(8) << "R.Acc";
		cout << "| " << setw(16) << "Amount";
		cout << "| " << setw(16) << "S.New Balance";
		cout << "| " << setw(16) << "R.New Balance";
		cout << "| " << setw(12) << "User" << "|\n";
		cout << "\t_________________________________________________________________________________________________________________________\n\n";
	}
	static void _PrintRecord(const clClient::stTransferLog& Record)
	{
		cout  << "\t| " << setw(30) << Record.Date;
		cout << "| " << setw(8) << Record.SenderClientAccountNumber;
		cout << "| " << setw(8) << Record.RecevierClientAccountNumber;
		cout << "| " << setw(16) << Record.Amount;
		cout << "| " << setw(16) << Record.RecevierClientNewBalance;
		cout << "| " << setw(16) << Record.RecevierClientNewBalance;
		cout << "| " << setw(12) << Record.Username << "|\n";
	}
	static void _PrintList(const vector <clClient::stTransferLog>& veRecords)
	{
		if (veRecords.size() == 0)
		{
			cout <<  "\t|" << clUtil::Spaces(35) << "There are no transfers registered in the system" << clUtil::Spaces(37) << "|\n";
		}
		else
		{
			for (const clClient::stTransferLog& Record : veRecords)
			{
				_PrintRecord(Record);
			}
		}
		cout  << "\t_________________________________________________________________________________________________________________________\n\n";
	}
public:
	static void ShowTransferLogListScreen()
	{
		vector <clClient::stTransferLog> veRecords = clClient::GetTransferLogList();

		DrawScreenHeader(clUtil::Spaces(6) + "Transfer Log List Screen", clUtil::Spaces(13) + to_string(veRecords.size()) + " Record(s)");

		_PrintHeader();
		_PrintList(veRecords);
	}
};