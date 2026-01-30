#pragma once
#include <iostream>
#include "clScreen.h"
#include "clUser.h"
#include "clUserInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clAddNewUserScreen : protected clScreen
{
private:
	static void _AddNewUser()
	{
		clUser User = clUser::GetNewUserObject();
		cout << "Add new user:\n";
		clUserInfo::ReadInfo(User);

		if (clInputValidation::ReadOption("Are you certain you want to register this user in the system? "))
		{
			User.Save();

			cout << "\n\n";
			clUserInfo::PrintInfo(User);
			cout << "User registration completed successfully.\n";
		}
	}

public:
	static void ShowAddNewUserScreen()
	{
		DrawScreenHeader(clUtil::Spaces(10) + "Add New Users Screen");

		_AddNewUser();
	}
};