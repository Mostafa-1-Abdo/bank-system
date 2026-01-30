#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clScreen.h"
#include "clUser.h"
#include "clUtil.h"
using namespace std;

class clUsersListScreen : protected clScreen
{
private:
	static void _PrintListHeader()
	{
		cout<< "\t________________________________________________________________________________________________________________________\n\n";
		cout << left;
		cout << "\t| " << setw(15) << "Username";
		cout << "| " << setw(25) << "Full Name";
		cout << "| " << setw(12) << "Phone";
		cout << "| " << setw(33) << "Email";
		cout << "| " << setw(10) << "Password";
		cout << "| " << setw(12) << "Permissions" << "|\n";
		cout << "\t________________________________________________________________________________________________________________________\n\n";
	}
	static void _PrintRecordLine(const clUser& User)
	{
		cout << "\t| " << setw(15) << User.Username;
		cout << "| " << setw(25) << User.FullName;
		cout << "| " << setw(12) << User.Phone;
		cout << "| " << setw(33) << User.Email;
		cout << "| " << setw(10) << User.Password;
		cout << "| " << setw(12) << User.Permissions << "|\n";
	}
	static void _PrintList(const vector <clUser>& veUsers)
	{
		for (const clUser& User : veUsers)
		{
			_PrintRecordLine(User);
		}
		cout << "\t________________________________________________________________________________________________________________________\n\n";
	}

public:
	static void ShowUsersListScreen()
	{
		vector <clUser> veUsers = clUser::GetUsersList();

		DrawScreenHeader(clUtil::Spaces(10) + "Users List Screen", clUtil::Spaces(14) + to_string(veUsers.size())  + " User(s)");

		_PrintListHeader();
		_PrintList(veUsers);
	}
};
