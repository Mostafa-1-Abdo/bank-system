#pragma once
#include <iostream>
#include "clClient.h"
#include "clClientInfo.h"
#include "clScreen.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clUpdateClientScreen : protected clScreen
{
private:
	enum enUpdateScreenOptions
	{
		FirstName = 1,LastName,Email,Phone,PinCode,Balance
	};

	static void _PrintUpdateOptions()
	{
		cout << "\n\n===============================\n";
		cout << clUtil::Spaces(8) << "Update Options\n";
		cout << "===============================\n";
		cout << "[1] First Name\n";
		cout << "[2] Last Name\n";
		cout << "[3] Email\n";
		cout << "[4] Phone\n";
		cout << "[5] Pin Code\n";
		cout << "[6] Balance\n";
		cout << "===============================";
	}
	static void _PerformUpdate(clClient &Client, string& ChangeMessage,const enUpdateScreenOptions Option)
	{
		switch (Option)
		{
		case enUpdateScreenOptions::FirstName:
			Client.FirstName = clInputValidation::ReadString("\nEnter first name : ");
			ChangeMessage = "First name : " + Client.FirstName + "\n";
			break;
		case enUpdateScreenOptions::LastName:
			Client.LastName = clInputValidation::ReadString("\nEnter last name : ");
			ChangeMessage = "Last name: " + Client.LastName + "\n";
			break;
		case enUpdateScreenOptions::Email:
			Client.Email = clInputValidation::ReadString("\nEnter Email : ");
			ChangeMessage = "Email: " + Client.Email+ "\n";
			break;
		case enUpdateScreenOptions::Phone:
			Client.Phone = clInputValidation::ReadString("\nEnter phone : ");
			ChangeMessage = "Phone : " + Client.Phone + "\n";
			break;
		case enUpdateScreenOptions::PinCode:
			Client.PinCode = clInputValidation::ReadString("\nEnter pin code : ");
			ChangeMessage = "Pinc ode : " + Client.PinCode+"\n";
			break;
		case enUpdateScreenOptions::Balance:
			Client.Balance = clInputValidation::ReadNonNegativeNumber<float>("\nEnter balance : ");
			ChangeMessage = "Balance : " + to_string(Client.Balance) + "\n";
			break;
		}
	}
	static void _Update()
	{
		string AccountNumber = clInputValidation::ReadString("Enter the client's account number : ");
		clClient Client = clClient::Find(AccountNumber);
		cout << "\n\n";
		if (Client.IsEmpty())
		{
			cout << "The client associated with account number (" << AccountNumber << ") could not be found in the system.\n";
			return;
		}
		clClientInfo::PrintInfo(Client);

		_PrintUpdateOptions();
		do
		{
			enUpdateScreenOptions Option = (enUpdateScreenOptions)clInputValidation::ReadNumberBetween<short>(1, 6, "\nSelect what you would like to change : ");

			string ChangeMessage;
			clClient Temp = Client;
			_PerformUpdate(Temp,  ChangeMessage, Option);

			if (clInputValidation::ReadOption("\nAre you certain you want to perform the change? "))
			{
				Client = Temp;
				Client.Save();

				cout << "\nChange saved successfully\n";
				cout << ChangeMessage;
			}
			cout << "_________________________________________\n\n";
			
		} while (clInputValidation::ReadOption("Would you like to make any further updates? "));

		cout << "\n\n";
		clClientInfo::PrintInfo(Client);
		cout << "Client updates completed successfully.\n";
	}

public:
	static void ShowUpdateClientScreen()
	{
		DrawScreenHeader(clUtil::Spaces(9) + "Update Client Screen");

		_Update();
	}
};
