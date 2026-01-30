#pragma once
#include <iostream>
#include "clUser.h"
#include "clUserInfo.h"
#include "clScreen.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clUpdateUserScreen : protected clScreen
{
private:
	enum enUpdateScreenOptions
	{
		FirstName = 1, LastName, Email, Phone, Username,Password, Permissions
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
		cout << "[5] Username\n";
		cout << "[6] Password\n";
		cout << "[7] Permissions\n";
		cout << "===============================";
	}
	static void _PerformUpdate(clUser& User, string& ChangeMessage, const enUpdateScreenOptions Option)
	{
		switch (Option)
		{
		case enUpdateScreenOptions::FirstName:
			User.FirstName = clInputValidation::ReadString("\nEnter first name : ");
			ChangeMessage = "First name : " + User.FirstName + "\n";
			break;
		case enUpdateScreenOptions::LastName:
			User.LastName = clInputValidation::ReadString("\nEnter last name : ");
			ChangeMessage = "Last name: " + User.LastName + "\n";
			break;
		case enUpdateScreenOptions::Email:
			User.Email = clInputValidation::ReadString("\nEnter Email : ");
			ChangeMessage = "Email: " + User.Email + "\n";
			break;
		case enUpdateScreenOptions::Phone:
			User.Phone = clInputValidation::ReadString("\nEnter phone : ");
			ChangeMessage = "Phone : " + User.Phone + "\n";
			break;
		case enUpdateScreenOptions::Username:
			User.Username = clInputValidation::ReadString("\nEnter username : ");
			ChangeMessage = "Username : " + User.Username + "\n";
			break;
		case enUpdateScreenOptions::Password:
			User.Password = clInputValidation::ReadString("\nEnter password : ");
			ChangeMessage = "Password : " + User.Password + "\n";
			break;
		case enUpdateScreenOptions::Permissions:
			cout << "\n";
			User.Permissions = clUserInfo::ReadPermissions();
			ChangeMessage = "Permissions : " + to_string(User.Permissions) + "\n";
			break;
		}
	}
	static void _Update()
	{
		string Username = clInputValidation::ReadString("Enter the user's username : ");
		clUser User = clUser::Find(Username);
		cout << "\n\n";
		if (User.IsEmpty())
		{
			cout << "The user associated with username (" << Username << ") could not be found in the system.\n";
			return;
		}
		clUserInfo::PrintInfo(User);

		_PrintUpdateOptions();
		do
		{
			enUpdateScreenOptions Option = (enUpdateScreenOptions)clInputValidation::ReadNumberBetween<short>(1, 7, "\nSelect what you would like to change : ");

			string OldUsername = User.Username;
			string ChangeMessage;
			clUser Temp = User;
			_PerformUpdate(Temp, ChangeMessage, Option);

			if (clInputValidation::ReadOption("\nAre you certain you want to perform the change? "))
			{
				User = Temp;
				User.Save(OldUsername);

				cout << "\nChange saved successfully\n";
				cout << ChangeMessage;
			}
			cout << "_________________________________________\n\n";

		} while (clInputValidation::ReadOption("Would you like to make any further updates? "));

		cout << "\n\n";
		clUserInfo::PrintInfo(User);
		cout << "User updates completed successfully.\n";
	}

public:
	static void ShowUpdateUserScreen()
	{
		DrawScreenHeader(clUtil::Spaces(9) + "Update User Screen");

		_Update();
	}
};
