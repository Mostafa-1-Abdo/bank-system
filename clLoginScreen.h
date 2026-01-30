#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clScreen.h"
#include "clUser.h"
#include "CurrentUser.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clLoginScreen : protected clScreen
{
private:
	

	static bool _Login()
	{
		vector <clUser> veUsers = clUser::GetUsersList();
		bool LoginFailed = false;
		short Trials = 3;
		string Username, Password;

		do
		{
			if (LoginFailed)
			{
				cout << "\nThe username or password entered is invalid. Please try again.\n";
				cout << "You have " << Trials << " attempts to try again.\n\n\n";

				if (Trials == 0)
				{
					cout << "You have been locked out after 3 failed attempts.\n\n";
					return false;
				}
			}

			Username = clInputValidation::ReadString("Enter Username : ");
			Password = clInputValidation::ReadString("Enter Password : ");

			 CurrentUser = clUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();
			Trials--;

		} while (LoginFailed);

		CurrentUser.SaveLoginInLogFile();
		return true;
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");

		clScreen::DrawScreenHeader(clUtil::Spaces(13) + "Login Screen");
		return _Login();
	}
};