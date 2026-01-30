#pragma once
#include <iostream>
#include "clScreen.h"
#include "clUser.h"
#include "clUserInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clDeleteUserScreen : protected clScreen
{
private:
	static void _Delete()
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

		if (clInputValidation::ReadOption("Are you certain you want to delete the user with username (" + Username + ") from the system? "))
		{
			User.Delete();
			cout << "\n\nUser deletion completed successfully.\n";
		}
	}

public:
	static void ShowDeleteUserScreen()
	{
		DrawScreenHeader(clUtil::Spaces(11) + "Delete User Screen");

		_Delete();
	}
};