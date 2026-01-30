#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "clScreen.h"
#include "clClient.h"
#include "clUtil.h"
using namespace std;

class clTotalBalancesScreen : protected clScreen
{
private:
	static void _PrintHeader(const int NumberOfClients)
	{
		cout  << "\t\t____________________________________________________________________________________________________\n\n";
		cout << left;
		cout << "\t\t| " << setw(15) << "Account Number";
		cout << "| " << setw(48) << "Client Name";
		cout << "| " << setw(30) << "Balance" << "|\n";
		cout << "\t\t____________________________________________________________________________________________________\n\n";
	}
	static void _PrintRecord(const clClient& Client)
	{
		cout << "\t\t| " << setw(15) << Client.AccountNumber;
		cout << "| " << setw(48) << Client.FullName;
		cout << "| " << setw(30) << Client.Balance << "|\n";
	}
	static void _PrintList(const vector <clClient>& veClients)
	{
		if (veClients.size()==0)
		{
			cout  << "\t\t\t\tThere are no clients registered in the system\n";
		}
		else
		{
			for (const clClient& Client : veClients)
			{
				_PrintRecord(Client);
			}
		}
	}
	
public:
	static void ShowTotalBalancesScreen()
	{
		vector <clClient> veClients = clClient::GetClientsList();
		int NumberOfClients = veClients.size();

		DrawScreenHeader(clUtil::Spaces(11) + "Total Balances Screen", clUtil::Spaces(7) + "Clients List(" + to_string(NumberOfClients) + ")" + " Client(s)");

		_PrintHeader(NumberOfClients);
		_PrintList(veClients);

		float TotalBalances = clClient::GetTotalBalances();
		cout  << "\t\t____________________________________________________________________________________________________\n\n";
		cout << "\t\tTotal Balances = " << TotalBalances << "\n";
		cout << "\t\tTotal Balances as number text = " << clUtil::ConvertNumberToText(TotalBalances) << "\n";
	}
};