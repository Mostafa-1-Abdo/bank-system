#pragma once
#include <iostream>
#include "clScreen.h"
#include "clUser.h"
#include "clUserInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clFindUserScreen : protected clScreen
{
private:
	static void _Find()
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
	}

public:
	static void ShowFindUserScreen()
	{
		DrawScreenHeader(clUtil::Spaces(12) + "Find User Screen");

		_Find();
	}
};