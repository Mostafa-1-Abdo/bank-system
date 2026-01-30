#pragma once
#include <iostream>
#include "clUser.h"
#include "clInputValidation.h"
using namespace std;

class clUserInfo
{
public:
	static short ReadPermissions()
	{
		short Permissions = 0;

		if (clInputValidation::ReadOption("Do you want to give him full access? "))
			Permissions += clUser::enPermissions::ShowList + clUser::enPermissions::AddClient + clUser::enPermissions::DeleteClient + clUser::enPermissions::UpdateClient + clUser::enPermissions::FindClient + clUser::enPermissions::Transactions + clUser::enPermissions::ManageUsers + clUser::enPermissions::LoginLog + clUser::enPermissions::CurrencyExchange;
		else
		{
			cout << "\nDo you want to give him access to:\n";

			if (clInputValidation::ReadOption("Show client list : "))
				Permissions += clUser::enPermissions::ShowList;
			if (clInputValidation::ReadOption("Add new client   : "))
				Permissions += clUser::enPermissions::AddClient;
			if (clInputValidation::ReadOption("Delete client    : "))
				Permissions += clUser::enPermissions::DeleteClient;
			if (clInputValidation::ReadOption("Update client    : "))
				Permissions += clUser::enPermissions::UpdateClient;
			if (clInputValidation::ReadOption("Find client      : "))
				Permissions += clUser::enPermissions::FindClient;
			if (clInputValidation::ReadOption("Transactions     : "))
				Permissions += clUser::enPermissions::Transactions;
			if (clInputValidation::ReadOption("Manage users     : "))
				Permissions += clUser::enPermissions::ManageUsers;
			if (clInputValidation::ReadOption("Login Log         : "))
				Permissions += clUser::enPermissions::LoginLog;
			if (clInputValidation::ReadOption("Currency Exchange : "))
				Permissions += clUser::enPermissions::CurrencyExchange;
		}

		return Permissions;
	}
	static void ReadInfo(clUser& User)
	{
		cout << "__________________________________\n";
		User.FirstName = clInputValidation::ReadString("Enter first name : ");
		User.LastName = clInputValidation::ReadString("Enter last name  : ");
		User.Email = clInputValidation::ReadString("Enter email      : ");
		User.Phone = clInputValidation::ReadString("Enter phone      : ");
		User.Username = clInputValidation::ReadString("Enter username   : ");
		while (clUser::IsExist(User.Username))
		{
			User.Username = clInputValidation::ReadString("This username is already in use, enter a different one : ");
		}
		User.Password = clInputValidation::ReadString("Enre password    : ");
		User.Permissions = ReadPermissions();
		cout << "__________________________________\n";
	}

	static void PrintInfo(const clUser& User)
	{
		cout << "User Card:\n";
		cout << "__________________________________\n";
		cout << "First Name     : " << User.FirstName << "\n";
		cout << "Last Name      : " << User.LastName << "\n";
		cout << "Full Name      : " << User.FullName << "\n";
		cout << "Email          : " << User.Email << "\n";
		cout << "Phone          : " << User.Phone << "\n";
		cout << "Username       : " << User.Username << "\n";
		cout << "Password       : " << User.Password << "\n";
		cout << "Permissions    : " << User.Permissions << "\n";
		cout << "__________________________________\n";
	}
};