#pragma once
#include <iostream>
#include "clClient.h"
#include "clClientInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clWithdrawScreen : protected clScreen
{
private:
	static void _Withdraw()
	{
		string AccountNumber = clInputValidation::ReadString("Enter client's account number : ");
		if (!clClient::IsExist(AccountNumber))
		{
			cout << "\n\nThe client associated with account number (" << AccountNumber << ") could not be found in the system.\n";
			return;
		}

		clClient Client = clClient::Find(AccountNumber);
		cout << "\n\n";
		clClientInfo::PrintInfo(Client);

		float WithdrawalAmount = clInputValidation::ReadNonNegativeNumber<float>("Enter withdrawal amount : ");

		if (clInputValidation::ReadOption("\n\nAre you sure you want to perform this withdrawal transaction for the client with account number(" + AccountNumber + ") ? "))
		{
			if (Client.Withdraw(WithdrawalAmount))
			{
				cout << "\n\nWithdrawal transaction completed successfully\n";
				cout << "New balance = " << Client.Balance << "\n";
			}
			else
				cout << "\n\nInsufficient balance. Withdrawal transaction was cancelled.\n";
		}
	}

public:
	static void ShowWithdrawScreen()
	{
		DrawScreenHeader(clUtil::Spaces(12) + "Withdraw Screen");

		_Withdraw();
	}
};