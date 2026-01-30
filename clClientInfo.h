#pragma once
#include <iostream>
#include "clClient.h"
#include "clInputValidation.h"
using namespace std;

class clClientInfo
{
public:
	static void ReadInfo(clClient& Client)
	{
		cout << "_________________________________________\n";
		Client.FirstName = clInputValidation::ReadString("Enter first name : ");
		Client.LastName = clInputValidation::ReadString("Enter last name  : ");
		Client.Email = clInputValidation::ReadString("Enter email      : ");
		Client.Phone = clInputValidation::ReadString("Enter phone      : ");
		Client.PinCode = clInputValidation::ReadString("Enter pin code   : ");
		Client.Balance = clInputValidation::ReadNonNegativeNumber<float>("Enre balance     : ");
		cout << "_________________________________________\n";
	}

	static void PrintInfo(const clClient& Client)
	{
		cout << "Client Card:\n";
		cout << "_________________________________________\n";
		cout << "First Name     : " << Client.FirstName << "\n";
		cout << "Last Name      : " << Client.LastName << "\n";
		cout << "Full Name      : " << Client.FullName << "\n";
		cout << "Email          : " << Client.Email << "\n";
		cout << "Phone          : " << Client.Phone << "\n";
		cout << "Account Number : " << Client.AccountNumber << "\n";
		cout << "Pin Code       : " << Client.PinCode << "\n";
		cout << "Balance        : " << Client.Balance << "\n";
		cout << "_________________________________________\n";
	}
};