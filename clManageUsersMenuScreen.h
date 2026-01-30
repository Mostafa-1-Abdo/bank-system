#pragma once
#include <iostream>
#include "clScreen.h"
#include "clUsersListScreen.h"
#include "clAddNewUserScreen.h"
#include "clDeleteUserScreen.h"
#include "clUpdateUserScreen.h"
#include "clFindUserScreen.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clManageUsersMenuScreen : protected clScreen
{
private:
	enum  enMangaeUsersMenuOption
	{
		UsersList = 1, AddNewUser, DeleteUser, UpdateUser, FindUser, MainMenue
	};

   static void _PrintManageUsersMenu()
	{
		DrawScreenHeader(clUtil::Spaces(10) + "Manage Users Screen");
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44) << clUtil::Spaces(15) <<"Manage Users Menu\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44) << "[1] List Users.\n";
		cout << clUtil::Spaces(44) << "[2] Add New User.\n";
		cout << clUtil::Spaces(44) << "[3] Delete User.\n";
		cout << clUtil::Spaces(44) << "[4] Update User.\n";
		cout << clUtil::Spaces(44) << "[5] Find User.\n";
		cout << clUtil::Spaces(44) << "[6] Main Menu.\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
	}
	
public:
	static void ShowManageUsersMainMenuScreen()
	{
		while (true)
		{
			_PrintManageUsersMenu();

			enMangaeUsersMenuOption Option = (enMangaeUsersMenuOption)clInputValidation::ReadNumberBetween<short>(1, 6, clUtil::Spaces(44) + "Choose what you would like to do : ");

			system("cls");

			switch (Option)
			{
			case enMangaeUsersMenuOption::UsersList:
				clUsersListScreen::ShowUsersListScreen();
				break;
			case enMangaeUsersMenuOption::AddNewUser:
				clAddNewUserScreen::ShowAddNewUserScreen();
				break;
			case enMangaeUsersMenuOption::DeleteUser:
				clDeleteUserScreen::ShowDeleteUserScreen();
				break;
			case enMangaeUsersMenuOption::UpdateUser:
				clUpdateUserScreen::ShowUpdateUserScreen();
				break;
			case enMangaeUsersMenuOption::FindUser:
				clFindUserScreen::ShowFindUserScreen();
				break;
			case enMangaeUsersMenuOption::MainMenue:
				return;
			}

			cout << endl << endl;
			WaitAndClear();
		}
	}
};
