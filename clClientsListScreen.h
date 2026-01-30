#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clScreen.h"
#include "clClient.h"
#include "clUtil.h"
using namespace std;

class clClientsListScreen : protected clScreen
{
private:
	static void _PrintListHeader()
	{
		cout << "\t________________________________________________________________________________________________________________________\n\n";
		cout << left;
		cout<< "\t| " << setw(15) << "Account Number";
		cout << "| " << setw(22) << "Full Name";
		cout << "| " << setw(12) << "Phone";
		cout << "| " << setw(33) << "Email";
		cout << "| " << setw(9) << "Pin Code";
		cout << "| " << setw(16) << "Balance" << "|\n";
		cout<< "\t________________________________________________________________________________________________________________________\n\n";
	}
	static void _PrintRecordLine(const clClient& Client)
	{
		cout << "\t| " << setw(15) << Client.AccountNumber;
		cout << "| " << setw(22) << Client.FullName;
		cout << "| " << setw(12) << Client.Phone;
		cout << "| " << setw(33) << Client.Email;
		cout << "| " << setw(9) << Client.PinCode;
		cout << "| " << setw(16) << Client.Balance << "|\n";
	}
	static void _PrintList(const vector <clClient>& veClients)
	{
		if (veClients.size() == 0)
		{
			cout  << "\t|" << clUtil::Spaces(36) << "There are no clients registered in the system" << clUtil::Spaces(34) << "|\n";
		}
		else
		{
			for (const clClient& Client : veClients)
			{
				_PrintRecordLine(Client);
			}
		}
		cout  << "\t________________________________________________________________________________________________________________________\n\n";
	}

public:
	static void ShowClientsListScreen()
	{
		vector <clClient> veClients = clClient::GetClientsList();

		DrawScreenHeader(clUtil::Spaces(9) + "Clients List Screen", clUtil::Spaces(13) +to_string(veClients.size()) + " Client(s)");

		_PrintListHeader();
		_PrintList(veClients);
	}
};