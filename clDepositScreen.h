#pragma once
#include <iostream>
#include "clScreen.h"
#include "clClient.h"
#include "clClientInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clDepositScreen : protected clScreen
{
private:
	static void _Deposit()
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

		float DepositAmount = clInputValidation::ReadNonNegativeNumber<float>("Enter deposit amount : ");

		if (clInputValidation::ReadOption("\n\nAre you sure you want to perform this deposit transaction for the client with account number (" + AccountNumber + ")? "))
		{
			Client.Deposit(DepositAmount);

			cout << "\n\nDeposit transaction completed successfully\n";
			cout << "New balance = " << Client.Balance << "\n";
		}
	}

public:
	static void ShowDepositScreen()
	{
		DrawScreenHeader(clUtil::Spaces(12) + "Deposit Screen");
		
		_Deposit();
	}
};