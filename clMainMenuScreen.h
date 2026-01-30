#pragma once
#include <iostream>
#include "clUtil.h"
#include "clInputValidation.h"
#include "clClientsListScreen.h"
#include "clAddNewClientScreen.h"
#include "clDeleteClientScreen.h"
#include "clUpdateClientScreen.h"
#include "clFindClinetScreen.h"
#include "clTransactionsMenuScreen.h"
#include "clUsersManagementMenuScreen.h"
#include "clLogoutScreen.h"
#include "clAccessDeniedScreen.h"
#include "clLoginLogListScreen.h"
#include "clCurrencyExchangeMenuScreen.h"
#include "clUser.h"
#include "CurrentUser.h"
using namespace std;

class clMainMenuScreen : protected clScreen
{
protected:
	enum enMainMenuOption
	{
		ClientsList = 1, AddClient, DeleteClient, UpdateClient, FindClient, Transactions, UsersManagement,LoginLog, CurrencyExchange, Logout
	};

	static clUser::enPermissions _ConvertOptionToPermission(const enMainMenuOption Option)
	{
		if (Option == enMainMenuOption::Logout)
			return clUser::Logout;

		short arPermissions[] = { 1,2,4,8,16,32,64,128,256 };
		return (clUser::enPermissions)arPermissions[Option - 1];
	}
	
	static void _PrintMainMenu()
	{
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44)<< clUtil::Spaces(19) << "Main Menu\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44) << "[1] Show Client List.\n";
		cout << clUtil::Spaces(44) << "[2] Add New Client.\n";
		cout << clUtil::Spaces(44) << "[3] Delete Client.\n";
		cout << clUtil::Spaces(44) << "[4] Update Client.\n";
		cout << clUtil::Spaces(44) << "[5] Find Client.\n";
		cout << clUtil::Spaces(44) << "[6] Transactions.\n";
		cout << clUtil::Spaces(44) << "[7] Users Management.\n";
		cout << clUtil::Spaces(44) << "[8] Loging Log.\n";
		cout << clUtil::Spaces(44) << "[9] Currency Exchange.\n";
		cout << clUtil::Spaces(44) << "[10] Logout.\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
	}

public :
	static void ShowMainMenuScreen()
	{
		system("cls");

		while (true)
		{
			DrawScreenHeader(clUtil::Spaces(14) + "Main Screen");
			clMainMenuScreen::_PrintMainMenu();
			enMainMenuOption Option = (enMainMenuOption)clInputValidation::ReadNumberBetween<short>(1, 10, clUtil::Spaces(44) + "Choose what you would like to do : ");

			system("cls");

			if (CurrentUser.DoHavePermissions(_ConvertOptionToPermission(Option)))
			{
				switch (Option)
				{
				case enMainMenuOption::ClientsList:
					clClientsListScreen::ShowClientsListScreen();
					break;
				case enMainMenuOption::AddClient:
					clAddNewClientScreen::ShowAddNewClientScreen();
					break;
				case enMainMenuOption::DeleteClient:
					clDeleteClientScreen::ShowDeleteClientScreen();
					break;
				case enMainMenuOption::UpdateClient:
					clUpdateClientScreen::ShowUpdateClientScreen();
					break;
				case enMainMenuOption::FindClient:
					clFindClientScreen::ShowFindClientScreen();
					break;
				case  enMainMenuOption::Transactions:
					clTransactionsMenuScreen::ShowTransactionsMenuScreen();
					continue;
				case enMainMenuOption::UsersManagement:
					clManageUsersMenuScreen::ShowUsersManagementMainMenuScreen();
					continue;
				case enMainMenuOption::LoginLog:
					clLoginLogListScreen::ShowLoginLogListScreen();
					break;
				case enMainMenuOption::CurrencyExchange:
					clCurrencyExchangeMenuScreen::ShowCurrencyExchangeMenuScreen();
					continue;
				case enMainMenuOption::Logout:
					clLogoutScreen::ShowLogoutScreen();
					return;
				}
			}
			else
			{
				clAccessDeniedScreen::ShowAccessDeniedScreen();
			}

			cout << endl << endl;
			WaitAndClear();
		}
}
};